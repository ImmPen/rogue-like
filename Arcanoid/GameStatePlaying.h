#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "GameStateData.h"
#include "Platform.h"
#include "Ball.h"
#include "Block.h"
#include "BlockFactory.h"
#include "Level.h"
#include "IObserver.h"
#include "Menu.h"
#include "SaveManager.h"
#include "Bonus.h"
#include "BonusFactory.h"
#include "BonusState.h"
#include <memory>
#include <variant>
#include <random>

namespace Arcanoid
{
	class GameStatePlayingData : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlayingData>
	{
	public:
		GameStatePlayingData();

		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

		void LoadNextLevel();

		void Notify(std::shared_ptr<IObservable> observable) override;		// IObserver

		GameMemento Save();													// Saves
		bool Load(const GameMemento& memento);

		void UpdateBonusStates();

	private:
		void CreateBlocks();
		bool IsWinCondition();
		void GetBallInverse(
			const sf::Vector2f& ballPosition,
			const sf::FloatRect& blockRect,
			bool& isNeedInverseDirectionX,
			bool& isNeedInverseDirectionY);

		//Resources
		sf::Font font;

		//Game data
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Block>> blocks;
		std::vector<std::shared_ptr<Bonus>> bonuses;

		std::shared_ptr<BonusState> bonusState = std::make_shared<BonusState>();

		std::unordered_map<BlockType, std::unique_ptr<BlockFactory>> blockFactories;
		std::unordered_map<BonusType, std::unique_ptr<BonusFactory>> bonusFactories;

		LevelLoader levelLoader;
		int currentLevel;

		//UI data
		sf::Text scoreText;

		//Random generator
		std::mt19937 gen;
		std::uniform_real_distribution<float> chance;
		std::uniform_int_distribution<int> type;
	};
}
