#pragma once
#include "Block.h"
namespace Arcanoid
{
	class MultipleHitBlock 
		: public Block
	{
		using Super = Block;
	public:
		MultipleHitBlock(const sf::Vector2f& position, int durability);
		MultipleHitBlock(const sf::Vector2f& position);
		~MultipleHitBlock() override = default;

		virtual BlockType GetType() override { return BlockType::MultipleHit; }

		void StageChange();
	private:
		void OnHit(CollisionType type) override;
	};

	class GlassBlock :
		public Block
	{
		using Super = Block;
	public:
		GlassBlock(const sf::Vector2f& position);
		~GlassBlock() override = default;

		CollisionType GetCollision(std::shared_ptr<ICollidable> collidable) const override;

		virtual BlockType GetType() override { return BlockType::Glass; }
	};
}
