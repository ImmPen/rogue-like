#pragma once
#include <SFML/Graphics.hpp>

namespace RogueLite
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
		const std::string FONT_PATH = RESOURCES_PATH + "Fonts/";
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 600;
		const std::string GAME_NAME = "RogueLite";

		const int NUM_RECORDS_IN_TABLE = 5;
		const float TIME_PER_FRAME = 1.f / 60.f;
	};
}

#define SETTINGS GameWorld::Instance()