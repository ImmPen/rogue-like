#include "Bonus.h"
#include <assert.h>
#include "Ball.h"
#include "Block.h"

namespace Arcanoid
{
	Bonus::Bonus(sf::Vector2f position) :
		GameObject(
			SETTINGS.RESOURCES_PATH + (std::string)"Powerups.png",
			SETTINGS.BONUS_RECT_IN_TEXTURE,
			position,
			SETTINGS.BONUS_WIDTH,
			SETTINGS.BONUS_HEIGHT),
		type(BonusType::NoBonus)
	{

	}
	void Bonus::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + SETTINGS.BONUS_SPEED * timeDelta * sf::Vector2f{ 0, 1 };
		this->sprite.setPosition(pos);
	}

	CollisionType Bonus::GetCollision(std::shared_ptr<ICollidable> collidable) const
	{
		auto ball = std::dynamic_pointer_cast<Ball>(collidable);
		auto block = std::dynamic_pointer_cast<Block>(collidable);
		if (ball || block)
		{
			return CollisionType::None;
		}
		return GetSpriteRect().intersects(collidable->GetRect()) ? CollisionType::Hit : CollisionType::None;
	}

	sf::FloatRect Bonus::GetRect()
	{
		return GetSpriteRect();
	}

	BonusType Bonus::GetTypeFromInt(int type)
	{
		switch (type)
		{
		case 1:
			return BonusType::OnBallBonus;
			break;
		case 2:
			return BonusType::OnBlockBonus;
			break;
		case 3:
			return BonusType::OnPlatformBonus;
			break;
		default:
			break;
		}
		return BonusType();
	}

	void Bonus::OnHit(CollisionType collisionType)
	{
		if (collisionType != CollisionType::None)
		{
			Emit();
		}
	}

	OnBallBonus::OnBallBonus(sf::Vector2f position) :
		Bonus(position)
	{
		type = BonusType::OnBallBonus;
		auto rect = SETTINGS.BONUS_RECT_IN_TEXTURE;
		rect.top = rect.top + rect.height;
		assert(this->texture.loadFromFile(SETTINGS.RESOURCES_PATH + "Powerups.png", rect));
	}

	OnBlockBonus::OnBlockBonus(sf::Vector2f position) :
		Bonus(position)
	{
		type = BonusType::OnBlockBonus;
		auto rect = SETTINGS.BONUS_RECT_IN_TEXTURE;
		rect.top = rect.top + 3 * rect.height;
		assert(this->texture.loadFromFile(SETTINGS.RESOURCES_PATH + "Powerups.png", rect));
	}

	OnPlatformBonus::OnPlatformBonus(sf::Vector2f position) :
		Bonus(position)
	{
		type = BonusType::OnPlatformBonus;
		auto rect = SETTINGS.BONUS_RECT_IN_TEXTURE;
		rect.top = rect.top + 2 * rect.height;
		assert(this->texture.loadFromFile(SETTINGS.RESOURCES_PATH + "Powerups.png", rect));
	}

}