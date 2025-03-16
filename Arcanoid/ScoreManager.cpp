#include "ScoreManager.h"
#include "Block.h"
#include "GameSettings.h"
#include <fstream>
#include "Application.h"

namespace Arcanoid
{
	void ScoreManager::ClearScore()
	{
		totalScore = 0;
	}

	void ScoreManager::AddScore(int inc)
	{
		totalScore += inc;
	}

	int ScoreManager::GetScore()
	{
		return totalScore;
	}

	void ScoreManager::SetScore(int sc)
	{
		this->totalScore = sc;
	}

	std::multiset<int> ScoreManager::GetRecordsTable() const
	{
		return this->recordsTable;
	}

	void ScoreManager::AddEntryToTable()
	{
		this->recordsTable.emplace(totalScore);
	}

	void ScoreManager::LoadTableFromFile(std::string tablePath)
	{
		std::ifstream in(tablePath);
		if (!in.is_open())
		{
			for (int i = 0; i < SETTINGS.NUM_RECORDS_IN_TABLE; i++)
			{
				this->recordsTable.emplace(0);
			}
		}
		else
		{
			while (!in.eof())
			{
				int record;
				while (in >> record)
				{
					this->recordsTable.emplace(record);
				}
			}
		}
		in.close();
	}

	void ScoreManager::TypeTableToFile(std::string tablePath)
	{
		std::fstream out(tablePath);
		int i = 0;
		for (auto it = this->recordsTable.rbegin(); it != this->recordsTable.rend() && i < SETTINGS.NUM_RECORDS_IN_TABLE; it++, i++)
		{
			out << *it << "\n";
		}
		out.close();
	}
	void ScoreManager::Notify(std::shared_ptr<IObservable> observable)
	{
		Game& game = Application::Instance().GetGame();
		if (auto block = std::dynamic_pointer_cast<Block>(observable); block) 
		{
			if (block->IsBroken())
			{
				AddScore(block->GetScore());
			}
		}
	}
}
