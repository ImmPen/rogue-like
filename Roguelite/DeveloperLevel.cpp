#include "DeveloperLevel.h"

namespace RogueLite
{
	void DeveloperLevel::Start()
	{
		player = std::make_shared<Player>();
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