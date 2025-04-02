#include "DeveloperLevel.h"

namespace RogueLite
{
	void DeveloperLevel::Start()
	{
		player = std::make_shared<Player>();
		enemy = std::make_shared<Enemy>(player.get());
		music = std::make_shared<BackgroundMusic>();
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