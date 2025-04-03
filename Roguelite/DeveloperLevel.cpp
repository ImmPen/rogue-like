#include "DeveloperLevel.h"

namespace RogueLite
{
	void DeveloperLevel::Start()
	{
		music = std::make_shared<BackgroundMusic>();
		for (int i = -20; i < 20; i++)
		{
			for (int j = -20; j < 20; j++)
			{
				floor.push_back(std::make_shared<Floor>(Engine::Vector2Df{ i * 32.f, j * 32.f }, 4));
			}
			walls.push_back(std::make_shared<Wall>(Engine::Vector2Df{ i * 32.f, 20 * 32.f }, 36));
			walls.push_back(std::make_shared<Wall>(Engine::Vector2Df{ i * 32.f, -20 * 32.f }, 36));
			walls.push_back(std::make_shared<Wall>(Engine::Vector2Df{ -20 * 32.f, i * 32.f }, 36));
			walls.push_back(std::make_shared<Wall>(Engine::Vector2Df{ 20 * 32.f, i * 32.f }, 36));
		}
		player = std::make_shared<Player>();
		enemy = std::make_shared<Enemy>(player.get());
	}

	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}

	void DeveloperLevel::Stop()
	{
		Engine::GameWorld::Instance()->Clear();
	}
}