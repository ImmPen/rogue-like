#include "pch.h"
#include "PhysicsSystem.h"


namespace Engine
{
    PhysicsSystem* Engine::PhysicsSystem::Instance()
    {
        static PhysicsSystem physicsSystem;
        return &physicsSystem;
    }

    void PhysicsSystem::Update()
    {
        for (int i = 0; i < colliders.size(); i++)
        {
            auto body = colliders[i]->GetGameObject()->GetComponent<RigidbodyComponent>();
            if (body->GetKinematic())
            {
                continue;
            }

            for (int j = 0; j < colliders.size(); j++)
            {
                if (j == i)
                {
                    continue;
                }

                sf::FloatRect intersection;
                if (colliders[i]->bounds.intersects(colliders[j]->bounds, intersection))
                {
                    if (colliders[i]->isTrigger != colliders[j]->isTrigger)
                    {
                        if (triggersEnteredPair.find(colliders[i]) == triggersEnteredPair.end()
                            && triggersEnteredPair.find(colliders[j]) == triggersEnteredPair.end())
                        {
                            auto trigger = new Trigger(colliders[i], colliders[j]);
                            colliders[i]->OnTriggerEnter(*trigger);
                            colliders[j]->OnTriggerEnter(*trigger);

                            triggersEnteredPair.emplace(colliders[i], colliders[j]);
                        }
                    }
                    else if (!colliders[i]->isTrigger)
                    {
                        float intersectionWidth = intersection.width;
                        float intersectionHeight = intersection.height;
                        Vector2Df intersectionPosition = { (float)(intersection.left - 0.5 * intersectionWidth),
                                                           (float)(intersection.top - 0.5 * intersectionHeight) };

                        Vector2Df aPostion = { colliders[i]->bounds.left, colliders[i]->bounds.top };
                        auto aTransform = colliders[i]->GetGameObject()->GetComponent<TransformComponent>();

                        if (intersectionWidth > intersectionHeight)
                        {
                            if (intersectionPosition.y > aPostion.y)
                            {
                                aTransform->MoveBy({ 0, -intersectionHeight });
                                LOG_INFO("Top collision");
                            }
                            else
                            {
                                aTransform->MoveBy({ 0, intersectionHeight });
                                LOG_INFO("Down Collision");
                            }
                        }
                        else
                        {
                            if (intersectionPosition.x > aPostion.x)
                            {
                                aTransform->MoveBy({ -intersectionWidth, 0 });
                                LOG_INFO("Right collision");
                            }
                            else
                            {
                                aTransform->MoveBy({ intersectionWidth, 0 });
                                LOG_INFO("Left Collision");
                            }
                        }

                        auto collision = new Collision(colliders[i], colliders[j], intersection);
                        colliders[i]->OnCollision(*collision);
                        colliders[j]->OnCollision(*collision);
                    }
                }
            }
        }
        for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair;
            triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
        {
            ++nextTriggeredPair;
            if (!triggeredPair->first->bounds.intersects(triggeredPair->second->bounds))
            {
                auto trigger = new Trigger(triggeredPair->first, triggeredPair->second);
                triggeredPair->first->OnTriggerExit(*trigger);
                triggeredPair->second->OnTriggerExit(*trigger);

                triggersEnteredPair.erase(triggeredPair);
            }
        }
    }

    float PhysicsSystem::GetFixedDeltaTime() const
    {
        return fixedDeltaTime;
    }

    void PhysicsSystem::Subscribe(ColliderComponent* collider)
    {
        //LOG_INFO("Subscribe" + std::to_string(collider));
        colliders.push_back(collider);
    }

    void PhysicsSystem::Unsubscribe(ColliderComponent* collider)
    {
        //LOG_INFO("Unsubscribe" + std::to_string(collider));
        colliders.erase(std::remove_if(colliders.begin(), colliders.end(),
            [collider](ColliderComponent* obj) { return obj == collider; }), colliders.end());

    }

}
