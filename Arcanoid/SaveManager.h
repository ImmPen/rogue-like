#pragma once
#include <memory>
#include "GameSettings.h"
#include "Block.h"


namespace Arcanoid
{
	class Visitor				//Паттерн Visitor - для преобразования GameMemento в бинарник и обратно
	{
		
	};

	class Serializer : public Visitor	
	{

	};

	class Deserializer : public Visitor
	{

	};

	class GameMemento
	{
	public:
		GameMemento() = default;
		GameMemento(std::vector<std::shared_ptr<Block>> blc, int sc, int lvl) :
			score(sc), level(lvl)
		{
			for (auto element : blc)
			{
				auto type = element.get()->GetType();
				auto rect = element.get()->GetRect();
				sf::Vector2i position = { (int)rect.left / SETTINGS.BLOCK_WIDTH, ((int)rect.top / SETTINGS.BLOCK_HEIGHT) + 1 };
				blocks.push_back(std::make_pair(type, position));
			}
		}
		GameMemento(std::vector<std::pair<BlockType, sf::Vector2i>> blc, int sc, int lvl) :
			blocks(blc), score(sc), level(lvl)
		{

		}
		int GetScoreData() const { return score; }
		int GetLevel() const { return level; }
		std::vector<std::pair<BlockType, sf::Vector2i>> GetBlocks() const { return blocks; }
	private:
		std::vector<std::pair<BlockType, sf::Vector2i>> blocks;
		int score = 0;
		int level = 1;
	};

	/*
	* Как работают сейвы:
	* При инициализации GameStatePlaying всегда вызывается функция Load
	* Если файл saves.dat был в директории Resoures/, то восстанавливается состояние из него.
	* При этом сейв - файл удаляется из директории
	* При каждом выходе из игры через менюшку запоминается состояние игры и записывается в сейв - файл
	* Если при старте игры не было этого файла, то загружется дефолтное состояние новой игры
	*/

	class SaveManager
	{
	public:
		static SaveManager& Instance()
		{
			static SaveManager instance;
			return instance;
		}
		GameMemento LoadFromFile(std::string path);
		void SaveToFile(GameMemento memento);

	private:
		SaveManager() = default;
	};
}