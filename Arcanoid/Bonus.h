#pragma once
#include "GameObject.h"
#include "GameSettings.h"
#include "SFML/Graphics.hpp"
#include "Collidable.h"
#include "IObserver.h"

namespace Arcanoid
{
	enum class BonusType
	{
		NoBonus,
		OnBallBonus,
		OnBlockBonus,
		OnPlatformBonus
	};

	class Bonus :
		public GameObject, public ICollidable, public IObservable//, IDelayedAction
	{
	protected:
		virtual void OnHit(CollisionType collisionType) override;
	protected:
		BonusType type;
	public:
		Bonus(sf::Vector2f position);
		virtual void Update(float timeDelta) override;
		virtual CollisionType GetCollision(std::shared_ptr<ICollidable> collidable) const override;
		virtual sf::FloatRect GetRect() override;
		BonusType GetType() { return type; }

		static BonusType GetTypeFromInt(int type);
	private:

	};

	class OnBallBonus : public Bonus
	{
	public:
		OnBallBonus(sf::Vector2f position);
	};
	class OnBlockBonus : public Bonus
	{
	public:
		OnBlockBonus(sf::Vector2f position);
	};
	class OnPlatformBonus : public Bonus
	{
	public:
		OnPlatformBonus(sf::Vector2f position);
	};
}
