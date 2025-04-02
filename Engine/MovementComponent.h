#pragma once
#include "TransformComponent.h"
#include "InputComponent.h"
#include "ChaseComponent.h"
#include "Vector.h"

namespace Engine
{
    class ENGINE_API MovementComponent :
        public Component
    {
    public:
        MovementComponent(GameObject* gameObject);
        ~MovementComponent();

        void Update(float deltaTime) override;
        void Render() override;

        void SetSpeed(float newSpeed);
        float GetSpeed();
        float GetAcceleration();

    private:
        InputComponent* input = nullptr;
        ChaseComponent* chaser = nullptr;
        TransformComponent* transform;

        bool isChaser;

        float speed = 0;
        Vector2Df prevPosition = { 0.f, 0.f };
        Vector2Df acceleration = { 0.f, 0.f };
    };
}
