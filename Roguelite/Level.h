#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Block.h"

namespace RogueLite
{
	struct Level
	{
		std::vector<std::pair<sf::Vector2i, BlockType>> blocks;
	};

	class LevelLoader
	{
	public:
		LevelLoader() { LoadLevelsFromFile(); };
		Level& GetLevel(int i);
		~LevelLoader() = default;
		int GetLevelCount();

	private:
		void LoadLevelsFromFile();

		static BlockType CharToBlockType(char symbol);
		std::vector<Level> levels;
	};
}
