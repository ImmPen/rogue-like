#include "GameStatePlaying.h"
#include <assert.h>
#include "Game.h"
#include "GameSettings.h"
#include "Application.h"
#include "VariousBlock.h"
#include "SoundManager.h"

namespace Arcanoid
{
	GameStatePlayingData::GameStatePlayingData() :
		gen(std::random_device{}()), chance(0, 1), type(1, 3)
	{

	}
	void GameStatePlayingData::Init()
	{
		currentLevel = 0;
		assert(this->font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/arial.ttf"));
		this->scoreText.setString("Score: 0");
		this->scoreText.setFont(this->font);
		this->scoreText.setFillColor(sf::Color::Red);
		this->scoreText.setCharacterSize(12);

		ScoreManager::Instance()->GetShared()->ClearScore();
		bonusState->AddObserver(weak_from_this());

		gameObjects.emplace_back(std::make_shared<Platform>(
			sf::Vector2f({
				static_cast<float>(SETTINGS.SCREEN_WIDTH / 2),
				static_cast<float>(SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT / 2) })));
		auto ball = std::make_shared<Ball>(sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT - SETTINGS.BALL_SIZE / 2.f }));
		ball->AddObserver(weak_from_this());
		gameObjects.emplace_back(ball);
		this->blockFactories.emplace(BlockType::Animated, std::make_unique<AnimatedBlockFactory>());
		this->blockFactories.emplace(BlockType::Unbreakable, std::make_unique<UnbreakableBlockFactory>());
		this->blockFactories.emplace(BlockType::MultipleHit, std::make_unique<MultipleHitBlockFactory>());
		this->blockFactories.emplace(BlockType::Glass, std::make_unique<GlassBlockFactory>());
		this->bonusFactories.emplace(BonusType::OnBallBonus, std::make_unique<OnBallBonusFactory>());
		this->bonusFactories.emplace(BonusType::OnBlockBonus, std::make_unique<OnBlockBonusFactory>());
		this->bonusFactories.emplace(BonusType::OnPlatformBonus, std::make_unique<OnPlatformBonusFactory>());
		if (!Load(SaveManager::Instance().LoadFromFile(SETTINGS.RESOURCES_PATH + "save.dat")))
		{
			CreateBlocks();
		}
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PauseGame();
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		static auto updateFunc = [timeDelta](auto element) { element->Update(timeDelta); };
		std::for_each(gameObjects.begin(), gameObjects.end(), updateFunc);
		std::for_each(blocks.begin(), blocks.end(), updateFunc);
		std::for_each(bonuses.begin(), bonuses.end(), updateFunc);
		bonusState->Update(timeDelta);

		std::shared_ptr<Platform> platform = std::static_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::static_pointer_cast<Ball>(gameObjects[1]);

		bool isNeedInverseX = false;
		bool isNeedInverseY = false;
		bool hasBrokeOneBlock = false;
		blocks.erase(										//removing blocks
			std::remove_if(blocks.begin(), blocks.end(),
			[ball, &hasBrokeOneBlock, &isNeedInverseX, &isNeedInverseY, this](auto block)
			{
				auto collisionType = block->GetCollision(ball);
				if (!hasBrokeOneBlock && block->CheckCollision(ball))
				{
					hasBrokeOneBlock = true;
					if (collisionType == CollisionType::Hit)
					{
						const auto ballPos = ball->GetPosition();
						const auto blockRect = block->GetRect();
						GetBallInverse(ballPos, blockRect, isNeedInverseX, isNeedInverseY);
					}
				}
				return block->IsBroken();
			}
			), blocks.end()
		);

		bonuses.erase(										//removing bonus capsules on hit with platform
			std::remove_if(bonuses.begin(), bonuses.end(),
				[platform, this](auto bonus)
				{
					bool outOfBounds = bonus->GetSpriteRect().top > SETTINGS.SCREEN_HEIGHT;
					bool collisionWithPlatform = bonus->CheckCollision(platform);
					return collisionWithPlatform || outOfBounds;
				}),
			bonuses.end()
		);

		

		if (isNeedInverseX)
		{
			ball->InvertDirectionX();
		}
		if (isNeedInverseY)
		{
			ball->InvertDirectionY();
		}
		auto isCollision = platform->CheckCollision(ball);
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();
		this->scoreText.setOrigin(GetTextOrigin(this->scoreText, { 0.5f, 0.f }));
		this->scoreText.setPosition(viewSize.x / 2.f, 50.f);
		window.draw(this->scoreText);

		static auto drawFunc = [&window](auto element) { element->Draw(window); };
		std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);
		std::for_each(blocks.begin(), blocks.end(), drawFunc);
		std::for_each(bonuses.begin(), bonuses.end(), drawFunc);
	}

	void GameStatePlayingData::LoadNextLevel()
	{
		if (currentLevel >= levelLoader.GetLevelCount() - 1) {
			Game& game = Application::Instance().GetGame();
			game.WinGame();
		}
		else
		{
			std::shared_ptr <Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
			std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
			platform->Restart();
			ball->Restart();
			blocks.clear();
			bonusState = std::make_shared<BonusState>();
			bonusState->AddObserver(weak_from_this());
			++currentLevel;
			CreateBlocks();
		}
	}

	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
		Game& game = Application::Instance().GetGame();
		if (auto block = std::dynamic_pointer_cast<Block>(observable); block) {
			this->scoreText.setString("Score: " + std::to_string(ScoreManager::Instance()->GetShared()->GetScore()));
			auto rand = chance(gen);
			if (rand < SETTINGS.BONUS_CHANCE)
			{
				auto bonusType = Bonus::GetTypeFromInt(type(gen));
				auto rect = block->GetRect();
				auto position = sf::Vector2f{ 
					rect.left + rect.width / 2.f, 
					rect.top + rect.height / 2.f };
				bonuses.emplace_back(bonusFactories.at(bonusType)->Create(position));
				bonuses.back()->AddObserver(weak_from_this());
			}
			if (IsWinCondition()) {
				game.LoadNextLevel();
			}
		}
		else if (auto ball = std::dynamic_pointer_cast<Ball>(observable); ball)
		{
			if (ball->GetPosition().y > gameObjects.front()->GetSpriteRect().top) {
				SoundManager::Instance().PlaySound(Sounds::gameOverSound);
				game.LoseGame();
			}
		}
		else if (auto bonus = std::dynamic_pointer_cast<Bonus>(observable); bonus)
		{
			auto type = bonus->GetType();
			switch (type)
			{
			case Arcanoid::BonusType::NoBonus:
				break;
			case Arcanoid::BonusType::OnBallBonus:
				bonusState = std::make_shared<OnBallDecorator>(bonusState);
				break;
			case Arcanoid::BonusType::OnBlockBonus:
				bonusState = std::make_shared<OnBlockDecorator>(bonusState);
				break;
			case Arcanoid::BonusType::OnPlatformBonus:
				bonusState = std::make_shared<OnPlatformDecorator>(bonusState);
				break;
			default:
				break;
			}
			if (type != BonusType::NoBonus)
			{
				bonusState->AddObserver(weak_from_this());
				UpdateBonusStates();
			}
		}
		else if (auto state = std::static_pointer_cast<BonusState>(observable); state)
		{
			UpdateBonusStates();
		}
	}

	GameMemento GameStatePlayingData::Save()
	{
		return GameMemento(blocks, ScoreManager::Instance()->GetScore(), currentLevel);
	}

	bool GameStatePlayingData::Load(const GameMemento& memento)
	{
		if (memento.GetBlocks().empty())
		{
			return false;
		}
		for (auto element : memento.GetBlocks())
		{
			sf::Vector2f position{
				(float)(SETTINGS.BLOCK_WIDTH / 2 + element.second.x * SETTINGS.BLOCK_WIDTH),
				(float)(element.second.y * SETTINGS.BLOCK_HEIGHT)
			};
			blocks.emplace_back(blockFactories.at(element.first)->Create(position));
			blocks.back()->AddObserver(ScoreManager::Instance()->GetShared());
			blocks.back()->AddObserver(weak_from_this());
		}
		currentLevel = memento.GetLevel();
		ScoreManager::Instance()->SetScore(memento.GetScoreData());
		scoreText.setString("Score: " + std::to_string(memento.GetScoreData()));
		return true;
	}

	void GameStatePlayingData::UpdateBonusStates()
	{
		std::shared_ptr<Platform> platform = std::static_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::static_pointer_cast<Ball>(gameObjects[1]);

		ball->DenyEffect();
		platform->DenyEffect();
		for (auto block : blocks)
		{
			block->DenyEffect();
		}

		auto bonusesFromDecorator = bonusState->GetBonus();
		for (auto bonus : bonusesFromDecorator)
		{
			switch (bonus)
			{
			case BonusType::NoBonus:
				break;
			case BonusType::OnBallBonus:
				ball->ApplyEffect();
				break;
			case BonusType::OnBlockBonus:
				for (auto block : blocks)
				{
					block->ApplyEffect();
				}
				break;
			case BonusType::OnPlatformBonus:
				platform->ApplyEffect();
				break;
			default:
				break;
			}
		}
	}

	void GameStatePlayingData::CreateBlocks()
	{
		auto self = weak_from_this();
		auto& level = levelLoader.GetLevel(currentLevel);
		for (auto block : level.blocks)
		{
			auto blockType = block.second;
			auto blockPostion = block.first;

			sf::Vector2f position{
				(float)(SETTINGS.BLOCK_WIDTH / 2 + blockPostion.x * SETTINGS.BLOCK_WIDTH),
				(float)(blockPostion.y * SETTINGS.BLOCK_HEIGHT)
			};
			blocks.emplace_back(blockFactories.at(blockType)->Create(position));
			auto scoreManager = ScoreManager::Instance()->GetShared();
			blocks.back()->AddObserver(scoreManager);
			blocks.back()->AddObserver(self);
		}
	}

	bool GameStatePlayingData::IsWinCondition()
	{
		for (auto element : blocks)
		{
			auto isUnbreakable = std::dynamic_pointer_cast<UnbreakableBlock>(element);
			auto isBroken = element->IsBroken();
			if (!isUnbreakable && !isBroken)
			{
				return false;
			}
		}
		return true;
	}

	void GameStatePlayingData::GetBallInverse(
		const sf::Vector2f& ballPosition,
		const sf::FloatRect& blockRect,
		bool& isNeedInverseDirectionX,
		bool& isNeedInverseDirectionY)
	{
		if (ballPosition.y > blockRect.top + blockRect.height)
		{
			isNeedInverseDirectionY = true;
		}
		if (ballPosition.y < blockRect.top)
		{
			isNeedInverseDirectionY = true;
		}
		if (ballPosition.x > blockRect.left + blockRect.width)
		{
			isNeedInverseDirectionX = true;
		}
		if (ballPosition.x < blockRect.left)
		{
			isNeedInverseDirectionX = true;
		}
	}
}
