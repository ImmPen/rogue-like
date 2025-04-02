#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "SpriteColliderComponent.h"
#include "ResourceSystem.h"
#include "ChaseComponent.h"
#include "MovementComponent.h"

#include "Player.h"

namespace RogueLite
{
	class Enemy
	{
	public:
		Enemy(Player* player);
		Engine::GameObject* GetGameObject();
	private:
		Engine::GameObject* gameObject;
	};
}