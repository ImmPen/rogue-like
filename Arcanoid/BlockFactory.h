#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include <variant>
namespace Arcanoid
{
	class Block;

	class BlockFactory
	{
	protected:

	public:
		virtual std::shared_ptr<Block> Create(const sf::Vector2f& position) = 0;
		virtual ~BlockFactory() = default;
	};

	class AnimatedBlockFactory : public BlockFactory
	{
	public:
		virtual std::shared_ptr<Block> Create(const sf::Vector2f& position) override;
		~AnimatedBlockFactory() = default;
	};

	class UnbreakableBlockFactory : public BlockFactory
	{
	public:
		std::shared_ptr<Block> Create(const sf::Vector2f& position) override;
		~UnbreakableBlockFactory() override = default;
	};

	class MultipleHitBlockFactory : public BlockFactory
	{
	public:
		virtual std::shared_ptr<Block> Create(const sf::Vector2f& position) override;
		~MultipleHitBlockFactory() = default;
	};

	class GlassBlockFactory : public BlockFactory
	{
	public:
		virtual std::shared_ptr<Block> Create(const sf::Vector2f& position) override;
		~GlassBlockFactory() override = default;
	};
}
