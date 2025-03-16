#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateData.h"

namespace Arcanoid
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		Pause,
		Records,
		Win,
		Saves
	};

	class GameState
	{
	public:
		GameState() = default;
		GameState(GameStateType type);
		GameState(const GameState& state) = delete;
		GameState(GameState&& state) noexcept { operator=(std::move(state)); }

		~GameState();

		GameState& operator= (const GameState& state) = delete;
		GameState& operator= (GameState&& state) noexcept
		{
			type = state.type;
			data = std::move(state.data);
			state.data = nullptr;
			return *this;
		}

		GameStateType GetType() const { return type; }

		template<class T>
		T* GetData() const
		{
			return static_cast<T*>(data.get());
		}
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(sf::Event& event);

	private:
		GameStateType type = GameStateType::None;
		std::shared_ptr<GameStateData> data = nullptr;
	};
}
