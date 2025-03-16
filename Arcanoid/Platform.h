#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "GameObject.h"
#include "Collidable.h"

namespace Arcanoid
{
	class Platform : public GameObject, public ICollidable
	{
	public:
		Platform(const sf::Vector2f& position);
		~Platform() override = default;
		void Update(float timeDelta) override;

		void OnHit(CollisionType type) override {}
		bool CheckCollision(std::shared_ptr<ICollidable> collidable) override;
		
		CollisionType GetCollision(std::shared_ptr<ICollidable> collidable) const override;

		sf::FloatRect GetRect() override { return GetSpriteRect(); }

		void ApplyEffect();
		void DenyEffect();
	private:
		void Move(float speed);
	};
}
