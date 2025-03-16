#include "Block.h"
#include "GameSettings.h"
#include <assert.h>
#include "Sprite.h"
#include "Ball.h"

namespace Arcanoid
{
	void Block::OnHit(CollisionType type)
	{
		if (type != CollisionType::None)
		{
			this->hitCount -= hitDecrease;
			if (IsBroken())
			{
				Emit();
			}
		}	
	}

	int Block::BlockTypeToColorNum(BlockType type)
	{
		switch (type)
		{
		case BlockType::Unbreakable:
			return 7;
		case BlockType::MultipleHit:
			return 7;
		case BlockType::Glass:
			return 6;
		default:
			break;
		}
	}

	Block::Block(const sf::Vector2f& position, const int color)
		: GameObject(
			SETTINGS.RESOURCES_PATH + (std::string)"spritesheet-breakout.png",
			SETTINGS.BLOCK_RECT_IN_TEXTURE,
			position,
			SETTINGS.BLOCK_WIDTH,
			SETTINGS.BLOCK_HEIGHT)
	{
		auto rect = SETTINGS.BLOCK_RECT_IN_TEXTURE;
		this->color = color;
		rect.top = SETTINGS.BLOCK_RECT_IN_TEXTURE.top + this->color * SETTINGS.BLOCK_HEIGHT_ON_TILESET;
		assert(this->texture.loadFromFile(SETTINGS.RESOURCES_PATH + "spritesheet-breakout.png", rect));
	}

	void Block::Update(float timeDelta)
	{

	}

	CollisionType Block::GetCollision(std::shared_ptr<ICollidable> collidableObject) const
	{
		return GetSpriteRect().intersects(collidableObject->GetRect()) ? CollisionType::Hit : CollisionType::None;
	}

	bool Block::IsBroken() const
	{
		return this->hitCount <= 0;
	}

	int Block::GetScore()
	{
		return this->score;
	}

	void Block::ApplyEffect()
	{
		hitDecrease = SETTINGS.MAX_DURABILITY;
	}

	void Block::DenyEffect()
	{
		hitDecrease = 1;
	}

	void SmoothDestroyableBlock::OnHit(CollisionType type)
	{
		Super::OnHit(type);
		if (this->hitCount <= 0)
		{
			StartTimer(SETTINGS.BREAK_TIME);
		}
	}

	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position, const int color)
		:
		Block(position, color)
	{

	}

	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position)
		: Block(position, rand() % 6)
	{
	}

	void SmoothDestroyableBlock::Update(float deltaTime)
	{
		Super::Update(deltaTime);
		UpdateTimer(deltaTime);
	}

	CollisionType SmoothDestroyableBlock::GetCollision(std::shared_ptr<ICollidable> collidableObject) const
	{
		if (isTimerStarted || IsBroken())
		{
			return CollisionType::None;
		}
		return Super::GetCollision(collidableObject);
	}

	bool SmoothDestroyableBlock::IsBroken() const
	{
		return Super::IsBroken() && (isTimerEnded);
	}

	void SmoothDestroyableBlock::EachTickAction(float deltaTime)
	{
		const float timeSinceStartedAnimation = destroyTime - currentTime;
		const int currentFrame = static_cast<int>(timeSinceStartedAnimation / SETTINGS.TIME_ON_FRAME);
		sf::IntRect rectOnTileSet = SETTINGS.BLOCK_RECT_IN_TEXTURE;
		rectOnTileSet.top = SETTINGS.BLOCK_RECT_IN_TEXTURE.top + this->color * SETTINGS.BLOCK_HEIGHT_ON_TILESET;
		rectOnTileSet.left = SETTINGS.BLOCK_RECT_IN_TEXTURE.left + currentFrame * SETTINGS.BLOCK_WIDTH_ON_TILESET;
		assert(this->texture.loadFromFile(SETTINGS.RESOURCES_PATH + "spritesheet-breakout.png", rectOnTileSet));
	}

	void SmoothDestroyableBlock::UpdateTimer(float deltaTime)
	{
		IDelayedAction::UpdateTimer(deltaTime);
		if (IsBroken())
		{
			Emit();
		}
	}

	UnbreakableBlock::UnbreakableBlock(const sf::Vector2f& position)
		: Block(position, BlockTypeToColorNum(BlockType::Unbreakable))
	{
		hitDecrease = 0;
	}
}