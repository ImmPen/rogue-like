#pragma once
#include "TransformComponent.h"
#include "Logger.h"
#include <iostream>
#include <vector>
#include <string>

namespace Engine
{
	class TransformComponent;

	class ENGINE_API GameObject
	{
		friend class GameWorld;
		friend class TransformComponent;
	public:
		GameObject();
		GameObject(std::string newName);
		~GameObject();

		void Update(float deltaTime);
		void Render();

		std::string GetName() const;
		void Print(int depth = 0) const;

		template <typename T>
		T* AddComponent()
		{
			if constexpr (!std::is_base_of<Component, T>::value)
			{

				LOG_WARN("T must be derived from Component.");
				return nullptr;
			}
			if constexpr (std::is_same<T, TransformComponent>::value)
			{
				if (GetComponent<TransformComponent>() != nullptr)
				{
					LOG_WARN("Can't add Transform, because it will break the engine loop");
					return nullptr;
				}
			}
			T* newComponent = new T(this);
			components.push_back(newComponent);
			//LOG_INFO("Add new component: " + std::to_string(newComponent));
			return newComponent;
		}

		void RemoveComponent(Component* component)
		{
			components.erase(
				std::remove_if(
					components.begin(), components.end(),
					[component](Component* obj) {return obj == component; }), components.end());
			delete component;
			//LOG_INFO("Delete component");
		}

		template<typename T>
		T* GetComponent() const
		{
			for (const auto& component : components)
			{
				if (auto casted = dynamic_cast<T*>(component))
				{
					return casted;
				}
			}
			return nullptr;
		}

		template <typename T>
		T* GetComponentInChildren() const
		{
			T* component = GetComponent<T>();
			if (component != nullptr || children.size() == 0)
			{
				return component;
			}

			for (const auto& child : children)
			{
				T* childComponent = child->GetComponentInChildren<T>();
				if (childComponent != nullptr)
				{
					return childComponent;
				}
			}

			return nullptr;
		}

		template<typename T>
		std::vector<T*> GetComponents() const
		{
			std::vector<T*> result;
			for (const auto& component : components)
			{
				if (auto casted = dynamic_cast<T*>(component))
				{
					result.push_back(casted);
				}
			}
			return result;
		}
	private:
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
	private:
		std::string name;
		std::vector<Component*> components = {};
		std::vector<GameObject*> children = {};
	};
}
