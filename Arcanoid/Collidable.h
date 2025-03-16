#pragma once
#include <SFML/Graphics.hpp>

namespace Arcanoid
{
	enum class CollisionType
	{
		None,
		Hit,
		Overlap
	};
	class ICollidable
	{
	protected:
		virtual void OnHit(CollisionType collisionType) = 0;
	public:
		virtual bool CheckCollision(std::shared_ptr<ICollidable> collidable)
		{
			auto collisionType = GetCollision(collidable);
			if (collisionType != CollisionType::None)
			{
				OnHit(collisionType);
				collidable->OnHit(collisionType);
				return true;
			}
			return false;
		}
		virtual CollisionType GetCollision(std::shared_ptr<ICollidable> collidable) const = 0;
		virtual sf::FloatRect GetRect() = 0;
	};
}