#pragma once

#include "AudioComponent.h"
#include "GameWorld.h"
#include "ResourceSystem.h"
#include "GameObject.h"

namespace RogueLite
{
	class BackgroundMusic
	{
	public:
		BackgroundMusic();
		Engine::GameObject* GetGameObject();
	private:
		Engine::GameObject* gameObject;
	};
}
