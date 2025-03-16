#include "Level.h"
#include <assert.h>
#include <fstream>
#include <string>
#include "GameSettings.h"

namespace Arcanoid
{
	Level& LevelLoader::GetLevel(int i)
	{
		return levels.at(i);
	}

	int LevelLoader::GetLevelCount()
	{
		return levels.size();
	}

	void LevelLoader::LoadLevelsFromFile()
	{
		std::string filePath = SETTINGS.RESOURCES_PATH + "levels.txt";
		std::string line;
		std::ifstream file(filePath);
		int y = 0;
		while (std::getline(file, line))
		{
			if (line.rfind("level ", 0) == 0)
			{
				levels.emplace_back(Level());
				y = 0;
			}
			else
			{
				int x = 0;
				for (char c : line)
				{
					if (c != ' ')
					{
						levels.back().blocks.emplace_back(std::make_pair(sf::Vector2i(x, y), CharToBlockType(c)));
					}
					x++;
				}
			}
			y++;
		}
		file.close();
	}

	BlockType LevelLoader::CharToBlockType(char symbol)
	{
		BlockType block;
		switch (symbol)
		{
		case '0':
			block = BlockType::Animated;
			break;
		case '1':
			block = BlockType::Unbreakable;
			break;
		case '2':
			block = BlockType::MultipleHit;
			break;
		case '3':
			block = BlockType::Glass;
			break;
		default:
			assert(false);
			break;
		}
		return block;
	}
}