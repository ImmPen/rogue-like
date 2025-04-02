#pragma once
#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "BackgroundMusic.h"

namespace RogueLite
{

	class DeveloperLevel : public Engine::Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;
	private:
		std::shared_ptr<Player> player;
		std::shared_ptr<BackgroundMusic> music;
	};
}
