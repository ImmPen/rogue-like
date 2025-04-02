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
		direction = direction * (1 / direction.GetLength());
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

}