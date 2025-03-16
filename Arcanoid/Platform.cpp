#include "Platform.h"
#include "assert.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <algorithm>
#include "Application.h"

namespace Arcanoid
{
	Platform::Platform(const sf::Vector2f& position)
		: GameObject(
			SETTINGS.RESOURCES_PATH + "spritesheet-breakout.png",
			SETTINGS.PLATFORM_RECT_IN_TEXTURE,
			position,
			SETTINGS.PLATFORM_WIDTH, SETTINGS.PLATFORM_HEIGHT)
	{

	}
	void Platform::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->Move(-timeDelta * SETTINGS.PLATFORM_SPEED);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->Move(timeDelta * SETTINGS.PLATFORM_SPEED);
		}
	}

	bool Platform::CheckCollision(std::shared_ptr<ICollidable> collidable)
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball)
		{
			return false;
		}
		if (GetCollision(ball) != CollisionType::None)
		{
			auto rect = this->GetRect();
			auto ballPosOnPlatform = (ball->GetPosition().x - (rect.left + rect.width / 2)) / (rect.width / 2);
			ball->ChangeAngle(90 - 20 * ballPosOnPlatform);
			ICollidable::CheckCollision(collidable);
			SoundManager::Instance().PlaySound(Sounds::reboundSound);
			return true;
		}
		return	false;
	}

	CollisionType Platform::GetCollision(std::shared_ptr<ICollidable> collidable) const
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball)
		{
			return CollisionType::None;
		}
		auto sqr = [](float x) {
			return x * x;
			};

		const auto rect = this->GetSpriteRect();
		const auto ballPos = ball->GetPosition();

		if (ballPos.x < rect.left) {
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.0)
				? CollisionType::Hit : CollisionType::None;
		}

		if (ballPos.x > rect.left + rect.width) {
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.0)
				? CollisionType::Hit : CollisionType::None;
		}
		return std::fabs(ballPos.y - rect.top) <= SETTINGS.BALL_SIZE / 2.0
			? CollisionType::Hit : CollisionType::None;
	}

	void Platform::ApplyEffect()
	{
		sprite.setScale({ static_cast<float>(SETTINGS.SCALE * 1.2), static_cast<float>(SETTINGS.SCALE) });
	}

	void Platform::DenyEffect()
	{
		sprite.setScale({ static_cast<float>(SETTINGS.SCALE), static_cast<float>(SETTINGS.SCALE) });
	}

	void Platform::Move(float speed)
	{
		auto positon = this->sprite.getPosition();
		positon.x = std::clamp(positon.x + speed,
			SETTINGS.PLATFORM_WIDTH / 2.f,
			SETTINGS.SCREEN_WIDTH - SETTINGS.PLATFORM_WIDTH / 2.f);
		sprite.setPosition(positon);
	}
}