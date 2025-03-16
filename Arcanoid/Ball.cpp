#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>
#include <numbers>

namespace Arcanoid
{
	Ball::Ball(const sf::Vector2f& position)
		: GameObject(
			SETTINGS.RESOURCES_PATH + "spritesheet-breakout.png",
			SETTINGS.BALL_RECT_IN_TEXTURE,
			position,
			SETTINGS.BALL_SIZE, SETTINGS.BALL_SIZE)
	{
		const float angle = lastAngle;
		this->direction.x = std::cos(std::numbers::pi / 180 * angle);
		this->direction.y = std::sin(std::numbers::pi / 180 * angle);
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + speed * timeDelta * this->direction;
		this->sprite.setPosition(pos);

		if (pos.x - SETTINGS.BALL_SIZE / 2 <= 0 || pos.x + SETTINGS.BALL_SIZE / 2 >= SETTINGS.SCREEN_WIDTH) {
			InvertDirectionX();
		}

		if (pos.y - SETTINGS.BALL_SIZE / 2 <= 0 || pos.y + SETTINGS.BALL_SIZE / 2 >= SETTINGS.SCREEN_HEIGHT) {
			InvertDirectionY();
		}

		Emit();
	}

	void Ball::InvertDirectionX()
	{
		ChangeAngle(180 - lastAngle);
	}

	void Ball::InvertDirectionY()
	{
		ChangeAngle(-lastAngle);
	}

	CollisionType Ball::GetCollision(std::shared_ptr<ICollidable> collidableObject) const
	{
		return GetSpriteRect().intersects(collidableObject->GetRect()) ? CollisionType::Hit : CollisionType::None;
	}

	void Ball::ChangeAngle(float angle)
	{
		lastAngle = angle;
		lastAngle = lastAngle > 180 ? lastAngle - 360 : lastAngle;
		lastAngle = lastAngle < -180 ? lastAngle + 360 : lastAngle;
		this->direction.x = std::cos(std::numbers::pi * lastAngle / 180);
		this->direction.y = -1 * std::sin(std::numbers::pi * lastAngle / 180);
	}

	void Ball::ApplyEffect()
	{
		sprite.setColor(sf::Color::Red);
		speed = SETTINGS.BALL_SPEED * 1.5;
	}

	void Ball::DenyEffect()
	{
		sprite.setColor(sf::Color::White);
		speed = SETTINGS.BALL_SPEED;
	}

	void Ball::OnHit(CollisionType type)
	{
		if (type != CollisionType::None)
		{
			const float lower = -5.f;
			const float higher = 5.f;
			lastAngle += lower + (rand()) / (RAND_MAX / static_cast<float>(higher - lower));
			ChangeAngle(lastAngle);
		}
	}
}