#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

namespace Arcanoid
{
	class Bonus; 

	class BonusFactory
	{
	public:
		virtual std::shared_ptr<Bonus> Create(const sf::Vector2f& position) = 0;
	};

	class OnBallBonusFactory : public BonusFactory
	{
	public:
		virtual std::shared_ptr<Bonus> Create(const sf::Vector2f& position) override;
	};
	class OnBlockBonusFactory : public BonusFactory
	{
	public:
		virtual std::shared_ptr<Bonus> Create(const sf::Vector2f& position) override;
	};
	class OnPlatformBonusFactory : public BonusFactory
	{
	public:
		virtual std::shared_ptr<Bonus> Create(const sf::Vector2f& position) override;
	};

}

