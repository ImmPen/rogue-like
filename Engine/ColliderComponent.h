#pragma once
#include <vector>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Component.h"
#include "Collision.h"
#include "Trigger.h"

namespace Engine
{
    class ENGINE_API ColliderComponent :
        public Component
    {
    public:
        ColliderComponent(GameObject* gameObject);

        virtual void Update(float deltaTime) = 0;
        virtual void Render() = 0;

        void SetTrigger(bool newIsTrigger);

        void SubscribeCollision(std::function<void(Collision)> onCollisionAction);
        void UnSubscribeCollision(std::function<void(Collision)> onCollisionAction);

        void SubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);
        void UnSubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);

        void SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);
        void UnSubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);

        friend class PhysicsSystem;
    protected:
        sf::FloatRect bounds;
        bool isTrigger = false;

        void OnCollision(Collision collision);
        void OnTriggerEnter(Trigger trigger);
        void OnTriggerExit(Trigger trigger);

        std::vector<std::function<void(Collision)>> onCollisionActions;
        std::vector<std::function<void(Trigger)>> onTriggerEnterActions;
        std::vector<std::function<void(Trigger)>> onTriggerExitActions;
    };
}
