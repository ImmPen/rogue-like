#pragma once
#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "BackgroundMusic.h"
#include "Wall.h"
#include "Floor.h"
#include "Logger.h"

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
		std::shared_ptr<Enemy> enemy;
		std::vector<std::shared_ptr<Wall>> walls;
		std::vector<std::shared_ptr<Floor>> floor;
	};
}
