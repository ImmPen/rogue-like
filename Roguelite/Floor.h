#pragma once

#include "Vector.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"

namespace RogueLite
{
	class Floor
	{
	public:
		Floor(Engine::Vector2Df position, int textureMapIndex);
	private:
		Engine::GameObject* gameObject;
	};
}
