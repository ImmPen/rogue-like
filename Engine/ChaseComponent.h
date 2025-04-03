#pragma once

#include "TransformComponent.h"
#include "InputComponent.h"
#include "Vector.h"

namespace Engine
{
    class ENGINE_API ChaseComponent :
        public Component
    {
    public:
        ChaseComponent(GameObject* thisObject);
        ~ChaseComponent();

        void Update(float deltaTime) override;
        void Render() override;

        void SetChasedObject(GameObject* chasedObject);
        Vector2Df GetDirection();
    private:
        TransformComponent* chasedTransform;
        TransformComponent* transform;

        Vector2Df direction = { 0.f, 0.f };
        float seekDistance = 1000.f;
    };
}
