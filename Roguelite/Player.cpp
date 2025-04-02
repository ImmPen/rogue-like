#include "Player.h"

namespace RogueLite
{
    Player::Player()
    {
        gameObject = Engine::GameWorld::Instance()->CreateGameObject();

        auto playerRenderer = gameObject->AddComponent<Engine::SpriteRendererComponent>();
        playerRenderer->SetTexture(*Engine::ResourceSystem::Instance()->GetTextureShared("Ball"));
        playerRenderer->SetPixelSize(32, 32);

        auto playerCamera = gameObject->AddComponent<Engine::CameraComponent>();
        playerCamera->SetWindow(&Engine::RenderSystem::Instance()->GetMainWindow());
        playerCamera->SetBaseResolution(1280, 720);

        auto playerInput = gameObject->AddComponent<Engine::InputComponent>();

        auto playerCollider = gameObject->AddComponent<Engine::SpriteColliderComponent>();

        auto playerRigidbodyComponent = gameObject->AddComponent<Engine::RigidbodyComponent>();

        auto playerMovement = gameObject->AddComponent<Engine::MovementComponent>();
        playerMovement->SetSpeed(2000);
    }

    Engine::GameObject* Player::GetGameObject()
    {
        return gameObject;
    }
}
