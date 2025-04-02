#include "pch.h"
#include "MovementComponent.h"

namespace Engine
{
	MovementComponent::MovementComponent(GameObject* gameObject)
		: Component(gameObject)
	{
		transform = gameObject->GetComponent<TransformComponent>();
		input = gameObject->GetComponent<InputComponent>();
		chaser = gameObject->GetComponent<ChaseComponent>();
		if (input == nullptr && chaser == nullptr)
		{
			std::cout << "For movement need input or chaser component" << std::endl;
			gameObject->RemoveComponent(this);
		}
		isChaser = chaser != nullptr;
	}

	MovementComponent::~MovementComponent()
	{
	}

	void MovementComponent::Update(float deltaTime)
	{
		float xAxis, yAxis;
		if (chaser)
		{
			xAxis = chaser->GetDirection().x;
			yAxis = chaser->GetDirection().y;
		}
		else
		{
			xAxis = input->GetHorizontalAxis();
			yAxis = input->GetVertcalAxis();
		}

		transform->MoveBy(speed * deltaTime * Vector2Df{ xAxis, yAxis });
	}
	
	void MovementComponent::Render()
	{
	}

	void MovementComponent::SetSpeed(float newSpeed)
	{
		speed = newSpeed;
	}

	float MovementComponent::GetSpeed()
	{
		return speed;
	}

	float MovementComponent::GetAcceleration()
	{
		return acceleration.GetLength();
	}

}