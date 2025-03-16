#include "BonusFactory.h"
#include "Bonus.h"

namespace Arcanoid
{
	std::shared_ptr<Bonus> OnBallBonusFactory::Create(const sf::Vector2f& position)
	{
		return std::make_shared<OnBallBonus>(position);
	}
	std::shared_ptr<Bonus> OnBlockBonusFactory::Create(const sf::Vector2f& position)
	{
		return std::make_shared<OnBlockBonus>(position);
	}
	std::shared_ptr<Bonus> OnPlatformBonusFactory::Create(const sf::Vector2f& position)
	{
		return std::make_shared<OnPlatformBonus>(position);
	}
}
