#pragma once
#include <memory>
#include <set>
#include <string>
#include <mutex>
#include "IObserver.h"

namespace Arcanoid
{
	class ScoreManager : public IObserver, public std::enable_shared_from_this<ScoreManager>
	{
	public:
		void ClearScore();
		void AddScore(int inc);
		int GetScore();
		void SetScore(int sc);
		std::multiset<int> GetRecordsTable() const;
		void AddEntryToTable();
		void LoadTableFromFile(std::string tablePath);
		void TypeTableToFile(std::string tablePath);

		void Notify(std::shared_ptr<IObservable> observable) override;		//IObserver
		
		std::shared_ptr<ScoreManager> GetShared()
		{
			return shared_from_this();
		}
		static std::shared_ptr<ScoreManager> Instance()
		{
			static std::once_flag initFlag;
			static std::shared_ptr<ScoreManager> instance;
			std::call_once(initFlag, []() {
				instance = std::shared_ptr<ScoreManager>(new ScoreManager());
				});
			return instance;
		}
	private:
		ScoreManager() = default;
		std::multiset<int> recordsTable;
		int totalScore = 0;
	};
}


