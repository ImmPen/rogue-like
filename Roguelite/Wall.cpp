#include "Wall.h"


namespace RogueLite
{
	Wall::Wall(const Engine::Vector2Df position, int textureMapIndex)
	{
		gameObject = Engine::GameWorld::Instance()->CreateGameObject();

		auto transform = gameObject->GetComponent<Engine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<Engine::SpriteRendererComponent>();
		renderer->SetTexture(*Engine::ResourceSystem::Instance()->GetTextureMapElementShared("Walls", textureMapIndex));
		renderer->SetPixelSize(32, 32);

		auto rigidbody = gameObject->AddComponent<Engine::RigidbodyComponent>();
		rigidbody->SetKinematic(true);

		auto collider = gameObject->AddComponent<Engine::SpriteColliderComponent>();
	}
}
