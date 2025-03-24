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

	void GameWorld::DestroyGameObject(GameObject* gameObject)
	{
		markedToDestroyGameObjects.push_back(gameObject);
	}

	void GameWorld::Clear()
	{
		for (auto& object : gameObjects)
		{
			DestroyGameObjectImmedeately(object);
		}
	}

	GameWorld::~GameWorld()
	{
		gameObjects.clear();
		markedToDestroyGameObjects.clear();
	}

	void GameWorld::DestroyGameObjectImmedeately(GameObject* gameObject)
	{
		gameObjects.erase(
			std::remove_if(gameObjects.begin(), gameObjects.end(),
				[gameObject](auto obj)
				{
					retirn obj == gameObject;
				}),
				gameObjects.end());
		markedToDestroyGameObjects.erase(
			std::remove_if(markedToDestroyGameObjects.begin(), markedToDestroyGameObjects.end(),
				[gameObject](auto obj)
				{
					return gameObject == obj;
				}),
			markedToDestroyGameObjects.end()
		);
		delete gameObject;
	}
}