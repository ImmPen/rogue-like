#pragma once
#include <SFML/Graphics.hpp>

namespace Arcanoid
{
	class GameWorld
	{
	private:
		GameWorld() = default;
	public:
		static GameWorld& Instance()
		{
			static GameWorld instance;
			return instance;
		}

		const std::string RESOURCES_PATH = "./Resourses/";
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 600;
		const std::string GAME_NAME = "RogueLite";
		const float PLATFORM_SPEED = 150;
		const float BALL_SPEED = 250;
		const int PAUSE_DELAY = 3; //in seconds
		const int NUM_RECORDS_IN_TABLE = 5;
		const float TIME_PER_FRAME = 1.f / 60.f;

		const int BLOCK_WIDTH_ON_TILESET = 32;
		const int BLOCK_HEIGHT_ON_TILESET = 16;
		const int NUM_BLOCK_IN_ROW = 10;
		const int NUM_COLORS = 6;

		const int BLOCK_WIDTH = SCREEN_WIDTH / NUM_BLOCK_IN_ROW;
		const int SCALE = BLOCK_WIDTH / BLOCK_WIDTH_ON_TILESET;
		const int BLOCK_HEIGHT = BLOCK_HEIGHT_ON_TILESET * SCALE;
		const int PLATFORM_WIDTH_ON_TILESET = 48;
		const int PLATFORM_HEIGHT_ON_TILESET = 14;
		const int PLATFORM_WIDTH = PLATFORM_WIDTH_ON_TILESET * SCALE;
		const int PLATFORM_HEIGHT = PLATFORM_HEIGHT_ON_TILESET * SCALE;
		const int BALL_SIZE_ON_TILESET = 12;
		const int BALL_SIZE = BALL_SIZE_ON_TILESET * SCALE;

		const float BREAK_TIME = 1.f;
		const int BREAK_FRAMES_COUNT = 12;
		const float TIME_ON_FRAME = BREAK_TIME / (float)BREAK_FRAMES_COUNT;

		const int MAX_DURABILITY = 3;

		const sf::IntRect PLATFORM_RECT_IN_TEXTURE = sf::IntRect(32, 64, PLATFORM_WIDTH_ON_TILESET, PLATFORM_HEIGHT_ON_TILESET);
		const sf::IntRect BALL_RECT_IN_TEXTURE = sf::IntRect(50, 34, BALL_SIZE_ON_TILESET, BALL_SIZE_ON_TILESET);
		const sf::IntRect BLOCK_RECT_IN_TEXTURE = sf::IntRect(32, 176, BLOCK_WIDTH_ON_TILESET, BLOCK_HEIGHT_ON_TILESET);

		const float BONUS_CHANCE = 0.1;
		const int BONUS_WIDTH_ON_TILESET = 16;
		const int BONUS_HEIGHT_ON_TILESET = 8;
		const int BONUS_WIDTH = BONUS_WIDTH_ON_TILESET * SCALE;
		const int BONUS_HEIGHT = BONUS_HEIGHT_ON_TILESET * SCALE;
		const sf::IntRect BONUS_RECT_IN_TEXTURE = sf::IntRect(0, 0, BONUS_WIDTH_ON_TILESET, BONUS_HEIGHT_ON_TILESET);
		const int BONUS_SPEED = 300;
	};
}

#define SETTINGS GameWorld::Instance()