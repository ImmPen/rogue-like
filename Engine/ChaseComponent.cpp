#include "pch.h"
#include "ChaseComponent.h"
#include "GameObject.h"

namespace Engine
{
	ChaseComponent::ChaseComponent(GameObject* thisObject)
		: Component(thisObject)
	{
		transform = thisObject->GetComponent<TransformComponent>();
	}

	ChaseComponent::~ChaseComponent()
	{
	}

	void ChaseComponent::Update(float deltaTime)
	{
		direction = chasedTransform->GetWorldPosition() - transform->GetWorldPosition();
		float distance = direction.GetLength();
		direction = distance < seekDistance ? direction * (1 / distance) : Vector2Df{0.f, 0.f};
	}

	void ChaseComponent::Render()
	{
	}

	void ChaseComponent::SetChasedObject(GameObject* chasedObject)
	{
		chasedTransform = chasedObject->GetComponent<TransformComponent>();
	}

	Vector2Df ChaseComponent::GetDirection()
	{
		return direction;
	}

	void ChaseComponent::SetSeekDistance(float newDistance)
	{
		seekDistance = newDistance;
	}

}