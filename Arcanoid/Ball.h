#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Block.h"
#include "IObserver.h"
#include "GameSettings.h"

namespace Arcanoid
{
	class Ball : public GameObject, public ICollidable, public IObservable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() override = default;

		void Update(float timeDelta) override;

		void InvertDirectionX();
		void InvertDirectionY();

		CollisionType GetCollision(std::shared_ptr<ICollidable> collidableObject) const override;
		void ChangeAngle(float angle);

		sf::FloatRect GetRect() override { return GetSpriteRect(); }

		void ApplyEffect();
		void DenyEffect();
	private:
		float speed = SETTINGS.BALL_SPEED;
		void OnHit(CollisionType type) override;
		sf::Vector2f direction;
		float lastAngle = 90; // [-180; 180] degrees
	};
}
