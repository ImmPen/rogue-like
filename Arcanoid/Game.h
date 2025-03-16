#pragma once
#include <random>
#include <vector>
#include <unordered_map>
#include "SoundManager.h"
#include "GameSettings.h"
#include "GameState.h"
#include "ScoreManager.h"

namespace Arcanoid
{
	
	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	enum class GameOptions : std::uint8_t
	{
		MUSIC_ON = 0x01,
		SOUNDS_ON = 0x02,
		DEFAULT = MUSIC_ON | SOUNDS_ON,
		Empty = 0
	};

	class Game
	{
	public:
		Game();
		~Game();
		
		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);

		void StartGame();
		void PauseGame();
		void WinGame();
		void LoseGame();
		void UpdateGame(float timeDelta, sf::RenderWindow& window);
		void ExitAndSave();
		void QuitGame();
		void ShowRecords();
		void Exit();
		void LoadNextLevel();

		void PopState();
		
	private:

		void HandleWindowEvents(sf::RenderWindow& window);
		bool Update(float timer);
		void Draw(sf::RenderWindow& window);
		void Shutdown();

		void PushState(GameStateType stateType);
		void SwitchStateTo(GameStateType stateType);

		std::vector<GameState> gameStateStack;
		GameStateChangeType gameStateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;

		GameOptions options = GameOptions::DEFAULT;
	};
}
