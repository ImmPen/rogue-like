#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"
#include "SpriteColliderComponent.h"
#include "ResourceSystem.h"

namespace RogueLite
{
	class Wall
	{
	public:
		Wall(const Engine::Vector2Df position, int textureMapIndex);
	private:
		Engine::GameObject* gameObject;
	};
}
