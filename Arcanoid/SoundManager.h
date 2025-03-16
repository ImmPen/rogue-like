#pragma once
#include <SFML/Audio.hpp>
#include "IObserver.h"

namespace Arcanoid
{
	class Game;

	enum class Sounds
	{
		reboundSound,
		gameOverSound,
		menuHoverSound
	};

	class SoundManager
	{
	public:
		void PlaySound(Sounds sound);
		void PlayMusic();

		static SoundManager& Instance()
		{
			static SoundManager instance;
			return instance;
		}
	private:
		SoundManager();

		sf::SoundBuffer reboundBuffer;
		sf::SoundBuffer gameOverBuffer;
		sf::SoundBuffer menuHoverBuffer;

		sf::Sound reboundSound;
		sf::Sound gameOverSound;
		sf::Sound menuHoverSound;

		sf::Music music;
	};
}