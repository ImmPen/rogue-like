#include "pch.h"
#include "TransformComponent.h"

constexpr float PI = 3.1415926;

namespace Engine
{
	TransformComponent::TransformComponent(GameObject* gameObject) : 
		Component(gameObject)
	{	}

	void TransformComponent::Update(float deltaTime)
	{
	}

	void TransformComponent::Render()
	{
	}

	void TransformComponent::MoveBy(const Vector2Df& offset)
	{
		MoveBy(offset.x, offset.y);
		isUpdated = false;
	}

	void TransformComponent::MoveBy(float offsetX, float offsetY)
	{
		localPosition.x += offsetX;
		localPosition.y += offsetY;
		isUpdated = false;
	}

	void TransformComponent::SetWorldPosition(const Vector2Df& position)
	{
		SetWorldPosition(position.x, position.y);
		isUpdated = false;
	}

	void TransformComponent::SetWorldPosition(float positonX, float positonY)
	{
		Vector2Df newPosition = { positonX, positonY };
		if (parent == nullptr)
		{
			localPosition = newPosition;
		}
		else
		{
			Matrix2D newWorldTransform = CreateTransform(newPosition, GetWorldRotation(), GetWorldScale());
			localTransform = parent->GetWorldTransform().GetInversed() * newWorldTransform;

			SetLocalInfoFrom(localTransform);

			isUpdated = false;
			UpdateLocalTransform();
		}
	}

	void TransformComponent::SetLocalPosition(const Vector2Df& position)
	{
		SetLocalPosition(position.x, position.y);
		isUpdated = false;
	}

	void TransformComponent::SetLocalPosition(float positionX, float positionY)
	{
		localPosition.x = positionX;
		localPosition.y = positionY;
		isUpdated = false;
	}

	void TransformComponent::RotateBy(const float offset)
	{
		localRotation += offset;
		while (localRotation >= 360)
		{
			localRotation -= 360;
		}
		while (localRotation < 0)
		{
			localRotation += 360;
		}
		isUpdated = false;
	}

	void TransformComponent::SetWorldRotation(float angle)
	{
		if (parent == nullptr)
		{
			localRotation = angle;
		}
		else
		{
			Matrix2D newWorldTransform = CreateTransform(GetWorldPosition(), angle, GetWorldScale());
			localTransform = parent->GetWorldTransform().GetInversed() * newWorldTransform;

			SetLocalInfoFrom(localTransform);

			isUpdated = false;
			UpdateLocalTransform();
		}
	}

	void TransformComponent::SetLocalRotation(float angle)
	{
		localRotation = angle;
		while (localRotation >= 360)
		{
			localRotation -= 360;
		}
		while (localRotation < 0)
		{
			localRotation += 360;
		}
		isUpdated = false;
	}

	void TransformComponent::ScaleBy(const Vector2Df& scaleOffset)
	{
		ScaleBy(scaleOffset.x, scaleOffset.y);
	}

	void TransformComponent::ScaleBy(float scaleX, float scaleY)
	{
		scale.x *= scaleX;
		scale.y *= scaleY;
		isUpdated = false;
	}

	void TransformComponent::SetWorldScale(const Vector2Df& scale)
	{
		SetWorldScale(scale.x, scale.y);
		isUpdated = false;
	}

	void TransformComponent::SetWorldScale(float scaleX, float scaleY)
	{
		Vector2Df newScale = { scaleX, scaleY };
		if (parent == nullptr)
		{
			localScale = newScale;
		}
		else
		{
			Matrix2D newWorldTransform = CreateTransform(GetWorldPosition(), GetWorldRotation(), newScale);
			localTransform = parent->GetWorldTransform().GetInversed() * newWorldTransform;

			SetLocalInfoFrom(localTransform);

			isUpdated = false;
			UpdateLocalTransform();
		}
	}

	void TransformComponent::SetLocalScale(const Vector2Df& scale)
	{
		SetLocalScale(scale.x, scale.y);
		isUpdated = false;
	}

	void TransformComponent::SetLocalScale(float scaleX, float scaleY)
	{
		localScale.x = scaleX;
		localScale.y = scaleY;
		isUpdated = false;
	}

	const Vector2Df& Engine::TransformComponent::GetWorldPosition() const
	{
		UpdateLocalTransform();
		if (parent == nullptr)
		{
			return GetLocalPosition();
		}
		SetWorldInfoFrom(parent->GetWorldTransform() * localTransform);
		return position;
	}

	const Vector2Df& TransformComponent::GetLocalPosition() const
	{
		UpdateLocalTransform();
		return localPosition;
	}

	const float TransformComponent::GetWorldRotation() const
	{
		UpdateLocalTransform();
		if (parent == nullptr)
		{
			return GetLocalRotation();
		}
		SetWorldInfoFrom(parent->GetWorldTransform() * localTransform);
		return rotation;
	}

	const float TransformComponent::GetLocalRotation() const
	{
		UpdateLocalTransform();
		return localRotation;
	}

	const Vector2Df& Engine::TransformComponent::GetWorldScale() const
	{
		UpdateLocalTransform();
		if (parent == nullptr)
		{
			return GetLocalScale();
		}
		SetWorldInfoFrom(parent->GetWorldTransform() * localTransform);
		return scale;
	}

	const Vector2Df& TransformComponent::GetLocalScale() const
	{
		UpdateLocalTransform();
		return localScale;
	}

	void TransformComponent::SetParent(TransformComponent* newParent)
	{
		if (parent == nullptr && newParent != nullptr)
		{
			newParent->gameObject->AddChild(gameObject);
			localTransform = newParent->GetWorldTransform().GetInversed() * localTransform;
		}
		else if (parent != nullptr && newParent == nullptr)
		{
			parent->gameObject->RemoveChild(gameObject);
			localTransform = parent->GetWorldTransform() * localTransform;
		}
		else if (parent != nullptr && newParent != nullptr)
		{
			parent->gameObject->RemoveChild(gameObject);
			newParent->gameObject->AddChild(gameObject);
			localTransform = newParent->GetWorldTransform().GetInversed() * (parent->GetWorldTransform() * localTransform);
		}

		SetLocalInfoFrom(localTransform);

		parent = newParent;
		isUpdated = false;
	}

	TransformComponent* TransformComponent::GetParent() const
	{
		return parent;
	}

	Matrix2D TransformComponent::GetWorldTransform()
	{
		UpdateLocalTransform();

		if (parent == nullptr)
		{
			return localTransform;
		}

		return parent->GetWorldTransform() * localTransform;
	}

	void TransformComponent::Print()
	{
		std::cout << "Transform name : " << gameObject->GetName() << std::endl;

		std::cout << "Position" << std::endl;
		std::cout << "World: (" << GetWorldPosition().x << ", " << GetWorldPosition().y << ")" << std::endl;
		std::cout << "Local: (" << GetLocalPosition().x << ", " << GetLocalPosition().y << ")" << std::endl;

		std::cout << "Rotation" << std::endl;
		std::cout << "World: " << GetWorldRotation() << std::endl;
		std::cout << "Local: " << GetLocalRotation() << std::endl;

		std::cout << "Scale" << std::endl;
		std::cout << "World: (" << GetWorldScale().x << ", " << GetWorldScale().y << ")" << std::endl;
		std::cout << "Local: (" << GetLocalScale().x << ", " << GetLocalScale().y << ")" << std::endl;
	}

	void TransformComponent::SetWorldInfoFrom(const Matrix2D& transform) const
	{
		position.x = transform.GetMatrix()[0][2];
		position.y = transform.GetMatrix()[1][2];

		scale.x = std::sqrt(transform.GetMatrix()[0][0] * transform.GetMatrix()[0][0]
			+ transform.GetMatrix()[1][0] * transform.GetMatrix()[1][0]);
		scale.y = std::sqrt(transform.GetMatrix()[0][1] * transform.GetMatrix()[0][1]
			+ transform.GetMatrix()[1][1] * transform.GetMatrix()[1][1]);


		rotation = std::atan2(transform.GetMatrix()[0][1], transform.GetMatrix()[0][0]) * 180 / PI;
	}

	void TransformComponent::SetLocalInfoFrom(const Matrix2D& transform) const
	{
		localPosition.x = transform.GetMatrix()[0][2];
		localPosition.y = transform.GetMatrix()[1][2];

		localScale.x = std::sqrt(transform.GetMatrix()[0][0] * transform.GetMatrix()[0][0]
			+ transform.GetMatrix()[1][0] * transform.GetMatrix()[1][0]);
		localScale.y = std::sqrt(transform.GetMatrix()[0][1] * transform.GetMatrix()[0][1]
			+ transform.GetMatrix()[1][1] * transform.GetMatrix()[1][1]);


		localRotation = std::atan2(transform.GetMatrix()[0][1], transform.GetMatrix()[0][0]) * 180 / PI;
	}

	void TransformComponent::UpdateLocalTransform() const
	{
		if (!isUpdated)
		{
			localTransform = CreateTransform(localPosition, localRotation, localScale);
			isUpdated = true;
		}
	}

	void TransformComponent::UpdateLocalTransform(const Vector2Df& position, float rotation, const Vector2Df& scale) const
	{
		if (!isUpdated)
		{
			localPosition = position;
			localRotation = rotation;
			localScale = scale;
			UpdateLocalTransform();
			isUpdated = true;
		}
	}

	Matrix2D TransformComponent::CreateTransform(const Vector2Df& position, float rotation, const Vector2Df& scale) const
	{
		Matrix2D result{
			position, rotation, scale
		};
		return result;
	}


}
