#include "pch.h"
#include "GameWorld.h"

namespace Engine
{
	GameWorld* GameWorld::Instance()
	{
		static GameWorld instance;
		return &instance;
	}

	void GameWorld::Update(float deltaTime)
	{
		for (auto& object : gameObjects)
		{
			object->Update(deltaTime);
		}
	}

	void GameWorld::FixedUpdate(float deltaTime)
	{
		fixedCounter += deltaTime;
		if (fixedCounter > PhysicsSystem::Instance()->GetFixedDeltaTime())
		{
			fixedCounter -= PhysicsSystem::Instance()->GetFixedDeltaTime();
			PhysicsSystem::Instance()->Update();
		}
	}

	void GameWorld::Render()
	{
		for (auto& object : gameObjects)
		{
			object->Render();
		}
	}

	void GameWorld::LateUpdate()
	{
		for (auto& object : markedToDestroyGameObjects)
		{
			DestroyGameObjectImmedeately(object);
		}
	}

	GameObject* GameWorld::CreateGameObject()
	{
		auto newObject = new GameObject;
		gameObjects.push_back(newObject);
		return newObject;
	}

	GameObject* GameWorld::CreateGameObject(std::string name)
	{
		auto newObject = new GameObject(name);
		gameObjects.push_back(newObject);
		return newObject;
	}

	void GameWorld::DestroyGameObject(GameObject* gameObject)
	{
		markedToDestroyGameObjects.push_back(gameObject);
	}

	void GameWorld::Clear()
	{
		for (auto& object : gameObjects)
		{
			if (object == nullptr)
			{
				continue;
			}
			if (object->GetComponent<TransformComponent>()->GetParent() == nullptr)
			{
				DestroyGameObjectImmedeately(object);
			}
		}
	}

	void GameWorld::Print() const
	{
		for (auto& obj : gameObjects)
		{
			if (obj == nullptr)
			{
				continue;
			}
			if (obj->GetComponent<TransformComponent>()->GetParent() == nullptr)
			{
				obj->Print();
			}
		}
	}

	void GameWorld::DestroyGameObjectImmedeately(GameObject* gameObject)
	{
		auto parent = gameObject->GetComponent<TransformComponent>()->GetParent();
		if (parent != nullptr)
		{
			parent->GetGameObject()->RemoveChild(gameObject);
		}

		for (auto transform = gameObject->GetComponentInChildren<TransformComponent>(); 
			transform != nullptr; transform++)
		{

			GameObject* gameObjectToDelete = transform->GetGameObject();

			gameObjects.erase(
				std::remove_if(gameObjects.begin(), gameObjects.end(),
					[gameObjectToDelete](auto obj)
					{
						return obj == gameObjectToDelete;
					}),
				gameObjects.end());
			markedToDestroyGameObjects.erase(
				std::remove_if(markedToDestroyGameObjects.begin(), markedToDestroyGameObjects.end(),
					[gameObjectToDelete](auto obj)
					{
						return gameObjectToDelete == obj;
					}),
				markedToDestroyGameObjects.end()
			);
		}
		
		delete gameObject;
	}
}