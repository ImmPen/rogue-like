#include "Game.h"
#include <fstream>
#include <assert.h>
#include "GameStatePlaying.h"
#include "SaveManager.h"

namespace Arcanoid
{
	Game::Game()
	{
		this->gameStateChangeType = GameStateChangeType::None;
		this->pendingGameStateType = GameStateType::None;
		SwitchStateTo(GameStateType::MainMenu);
		
		std::string tablePath = SETTINGS.RESOURCES_PATH + "Records.txt";
		ScoreManager::Instance()->GetShared()->LoadTableFromFile(tablePath);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (this->gameStateStack.size() > 0)
			{
				this->gameStateStack.back().HandleWindowEvent(event);
			}
		}
	}
	
	void Game::Shutdown()
	{
		while (this->gameStateStack.size() > 0)
		{
			this->gameStateStack.pop_back();
		}
		this->gameStateChangeType = GameStateChangeType::None;
		this->pendingGameStateType = GameStateType::None;
		ScoreManager::Instance()->GetShared()->TypeTableToFile(SETTINGS.RESOURCES_PATH + "Records.txt");
	}

	bool Game::IsEnableOptions(GameOptions option) const
	{
		const bool isEnable = ((std::uint8_t)options & (std::uint8_t)option) != (std::uint8_t)GameOptions::Empty;
		return isEnable;
	}

	void Game::SetOption(GameOptions option, bool value)
	{
		if (value) {
			options = (GameOptions)((std::uint8_t)options | (std::uint8_t)option);
		}
		else {
			options = (GameOptions)((std::uint8_t)options & ~(std::uint8_t)option);
		}
	}
	
	bool Game::Update(float timer)
	{
		switch (this->gameStateChangeType)			// Обрабатываем смену стейтов
		{
		case GameStateChangeType::Pop:
			if (this->gameStateStack.size() > 0)
			{
				this->gameStateStack.pop_back();
			}
			break;
		case GameStateChangeType::Switch:
			while (this->gameStateStack.size() > 0)
			{
				this->gameStateStack.pop_back();
			}
			break;
		default:
			break;
		}
		if (this->pendingGameStateType != GameStateType::None)
		{
			this->gameStateStack.push_back(GameState(this->pendingGameStateType));
		}
		this->pendingGameStateType = GameStateType::None;
		this->gameStateChangeType = GameStateChangeType::None;

		if (this->gameStateStack.size() > 0)	// Обновляем игру
		{
			SoundManager::Instance().PlayMusic();
			this->gameStateStack.back().Update(timer);
			return true;
		}
		return false;	// Если в итоге стек стейтов пустой, то выходим из цикла
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (this->gameStateStack.size() > 0)
		{
			for (auto it = this->gameStateStack.begin(); it != this->gameStateStack.end(); it++)
			{
				it->Draw(window);
			}
		}
	}

	void Game::PushState(GameStateType stateType)
	{
		this->pendingGameStateType = stateType;
		this->gameStateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		this->pendingGameStateType = GameStateType::None;
		this->gameStateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType stateType)
	{
		this->pendingGameStateType = stateType;
		this->gameStateChangeType = GameStateChangeType::Switch;
	}

	void Game::StartGame()
	{
		SwitchStateTo(GameStateType::Playing);
	}

	void Game::PauseGame()
	{
		PushState(GameStateType::Pause);
	}

	void Game::WinGame()
	{
		ScoreManager::Instance()->GetShared()->AddEntryToTable();
		PushState(GameStateType::Win);
	}

	void Game::LoseGame()
	{
		ScoreManager::Instance()->GetShared()->AddEntryToTable();
		PushState(GameStateType::GameOver);
	}

	void Game::UpdateGame(float timeDelta, sf::RenderWindow& window)
	{
		HandleWindowEvents(window);

		if (Update(SETTINGS.TIME_PER_FRAME))
		{
			window.clear();

			Draw(window);

			window.display();
		}
		else
		{
			window.close();
		}
	}

	void Game::ExitAndSave()
	{
		SaveManager::Instance().SaveToFile(gameStateStack.front().GetData<GameStatePlayingData>()->Save());
		SwitchStateTo(GameStateType::MainMenu);
	}

	void Game::QuitGame()
	{
		SwitchStateTo(GameStateType::None);
	}

	void Game::ShowRecords()
	{
		SwitchStateTo(GameStateType::Records);
	}

	void Game::Exit()
	{
		SwitchStateTo(GameStateType::MainMenu);
	}

	void Game::LoadNextLevel()
	{
		assert(gameStateStack.back().GetType() == GameStateType::Playing);
		auto playingData = (gameStateStack.back().GetData<GameStatePlayingData>());
		playingData->LoadNextLevel();
	}
}
