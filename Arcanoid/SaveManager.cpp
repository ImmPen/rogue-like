#include "SaveManager.h"
#include "GameSettings.h"
#include <fstream>
#include <assert.h>
#include <stdio.h>

namespace Arcanoid
{
	GameMemento SaveManager::LoadFromFile(std::string path)
	{
		std::ifstream file(path, std::ios::binary);
		
		if (file.is_open())
		{
			int level;
			int score;
			std::vector<std::pair<BlockType, sf::Vector2i>> blocks;
			size_t vectorLenght;
			file.read(reinterpret_cast<char*>(&level), sizeof(level));
			file.read(reinterpret_cast<char*>(&score), sizeof(score));
			file.read(reinterpret_cast<char*>(&vectorLenght), sizeof(vectorLenght));
			for (size_t i = 0; i < vectorLenght; i++)
			{
				std::pair<BlockType, sf::Vector2i> element;
				file.read(reinterpret_cast<char*>(&element.first), sizeof(element.first));
				file.read(reinterpret_cast<char*>(&element.second), sizeof(element.second));
				blocks.push_back(element);
			}
			GameMemento memento(blocks, score, level);
			file.close();
			remove(path.c_str());
			return memento;
		}
		file.close();
		GameMemento memento;
		return memento;
	}

	void SaveManager::SaveToFile(GameMemento memento)
	{
		std::ofstream file(SETTINGS.RESOURCES_PATH + "save.dat", std::ios::binary);
		auto level = memento.GetLevel();
		auto score = memento.GetScoreData();
		auto blockVector = memento.GetBlocks();
		auto sizeVector = blockVector.size();
		file.write(reinterpret_cast<const char*>(&level), sizeof(level));
		file.write(reinterpret_cast<const char*>(&score), sizeof(score));
		file.write(reinterpret_cast<const char*>(&sizeVector), sizeof(sizeVector));
		for (auto element : blockVector)
		{
			file.write(reinterpret_cast<const char*>(&element.first), sizeof(element.first));
			file.write(reinterpret_cast<const char*>(&element.second), sizeof(element.second));
		}
		file.close();
	}
}