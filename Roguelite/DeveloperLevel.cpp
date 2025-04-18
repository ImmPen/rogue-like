#include "DeveloperLevel.h"

namespace RogueLite
{
	void DeveloperLevel::Start()
	{
		LOG_INFO("Starting developer level");
		music = std::make_shared<BackgroundMusic>();
		LOG_INFO("Created background music");
		for (int i = -20; i < 20; i++)
		{
			for (int j = -20; j < 20; j++)
			{
				floor.push_back(std::make_shared<Floor>(Engine::Vector2Df{ i * 32.f, j * 32.f }, 4));
				LOG_INFO("Created floor at position: " 
					+ std::to_string(i * 32.f) + " "
					+ std::to_string(j * 32.f));
			}
			walls.push_back(std::make_shared<Wall>(Engine::Vector2Df{ i * 32.f, 20 * 32.f }, 36));
			LOG_INFO("Created floor at position: "
				+ std::to_string(i * 32.f) + " "
				+ std::to_string(20 * 32.f));
			walls.push_back(std::make_shared<Wall>(Engine::Vector2Df{ i * 32.f, -20 * 32.f }, 36));
			LOG_INFO("Created floor at position: "
				+ std::to_string(i * 32.f) + " "
				+ std::to_string(-20 * 32.f));
			walls.push_back(std::make_shared<Wall>(Engine::Vector2Df{ -20 * 32.f, i * 32.f }, 36));
			LOG_INFO("Created floor at position: "
				+ std::to_string(-20 * 32.f) + " "
				+ std::to_string(i * 32.f));
			walls.push_back(std::make_shared<Wall>(Engine::Vector2Df{ 20 * 32.f, i * 32.f }, 36));
			LOG_INFO("Created floor at position: "
				+ std::to_string(20 * 32.f) + " "
				+ std::to_string(i * 32.f));
		}
		player = std::make_shared<Player>();
		LOG_INFO("Created player");
		enemy = std::make_shared<Enemy>(player.get());
		LOG_INFO("Created enemy");
	}

	void DeveloperLevel::Restart()
	{
		LOG_INFO("Restarting developer level");
		Stop();
		Start();
	}

	void DeveloperLevel::Stop()
	{
		LOG_INFO("Stopped developer level");
		Engine::GameWorld::Instance()->Clear();
	}
}