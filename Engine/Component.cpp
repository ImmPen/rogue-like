#include "pch.h"
#include "Component.h"
#include <iostream>

namespace Engine
{
	Component::Component(GameObject* gameObject)
		: gameObject(gameObject)
	{
	}

	Component::~Component()
	{
		std::cout << "Removed component: " << this << std::endl;
	}

	GameObject* Component::GetGameObject()
	{
		return gameObject;
	}
}

