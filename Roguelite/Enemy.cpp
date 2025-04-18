#include "Enemy.h"

namespace RogueLite
{
	RogueLite::Enemy::Enemy(Player* player)
	{
		gameObject = Engine::GameWorld::Instance()->CreateGameObject();

		auto enemyTransform = gameObject->GetComponent<Engine::TransformComponent>();
		enemyTransform->SetWorldPosition(500, 500);

		auto enemyRenderer = gameObject->AddComponent<Engine::SpriteRendererComponent>();
		enemyRenderer->SetTexture(*Engine::ResourceSystem::Instance()->GetTextureShared("Ball"));
		enemyRenderer->SetPixelSize(32, 32);
		//TODO:		Сделать красным

		auto enemyChaser = gameObject->AddComponent<Engine::ChaseComponent>();
		enemyChaser->SetChasedObject(player->GetGameObject());
		enemyChaser->SetSeekDistance(500);
		
		auto enemyCollider = gameObject->AddComponent<Engine::SpriteColliderComponent>();

		auto enemyRigidbodyComponent = gameObject->AddComponent<Engine::RigidbodyComponent>();
		
		auto enemyMovement = gameObject->AddComponent<Engine::MovementComponent>();
		enemyMovement->SetSpeed(100);
	}

	Engine::GameObject* Enemy::GetGameObject()
	{
		return gameObject;
	}
}