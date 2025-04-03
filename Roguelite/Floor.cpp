#include "Floor.h"

namespace RogueLite
{
	Floor::Floor(Engine::Vector2Df position, int textureMapIndex)
	{
		gameObject = Engine::GameWorld::Instance()->CreateGameObject();

		auto transform = gameObject->GetComponent<Engine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<Engine::SpriteRendererComponent>();
		renderer->SetTexture(*Engine::ResourceSystem::Instance()->GetTextureMapElementShared("Floor", textureMapIndex));
		renderer->SetPixelSize(32, 32);
	}
}
