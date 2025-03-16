#include "VariousBlock.h"
#include "GameSettings.h"
#include <assert.h>
namespace Arcanoid
{
	MultipleHitBlock::MultipleHitBlock(const sf::Vector2f& position, int durability)
		:Block(position, BlockTypeToColorNum(BlockType::MultipleHit))
	{
		auto rect = SETTINGS.BLOCK_RECT_IN_TEXTURE;
		rect.top = SETTINGS.BLOCK_RECT_IN_TEXTURE.top + this->color * SETTINGS.BLOCK_HEIGHT_ON_TILESET;
		rect.left = SETTINGS.BLOCK_RECT_IN_TEXTURE.left + SETTINGS.BLOCK_WIDTH_ON_TILESET;
		assert(this->texture.loadFromFile(SETTINGS.RESOURCES_PATH + "spritesheet-breakout.png", rect));
		this->hitCount = durability;
		this->score *= durability;
	}
	MultipleHitBlock::MultipleHitBlock(const sf::Vector2f& position) 
		: MultipleHitBlock(position, SETTINGS.MAX_DURABILITY)
	{
	}
	void MultipleHitBlock::StageChange()
	{
		this->sprite.setColor(sf::Color(255, 255, 255, (int)(this->hitCount / (float)SETTINGS.MAX_DURABILITY * 255)));
	}
	void MultipleHitBlock::OnHit(CollisionType type)
	{
		Super::OnHit(type);
		StageChange();
	}
	GlassBlock::GlassBlock(const sf::Vector2f& position)
		: Block(position, BlockTypeToColorNum(BlockType::Glass))
	{
		this->score /= 2;
	}
	CollisionType GlassBlock::GetCollision(std::shared_ptr<ICollidable> collidable) const 
	{
		return Super::GetCollision(collidable) == CollisionType::Hit
			? CollisionType::Overlap : CollisionType::None;
	}
}