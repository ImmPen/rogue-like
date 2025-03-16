#include "BlockFactory.h"
#include "Block.h"
#include "VariousBlock.h"
#include "Bonus.h"

namespace Arcanoid
{
    std::shared_ptr<Block> AnimatedBlockFactory::Create(const sf::Vector2f& position)
    {
        return std::make_shared<SmoothDestroyableBlock>(position);
    }
    std::shared_ptr<Block> UnbreakableBlockFactory::Create(const sf::Vector2f& position)
    {
        return std::make_shared<UnbreakableBlock>(position);
    }
    std::shared_ptr<Block> MultipleHitBlockFactory::Create(const sf::Vector2f& position)
    {
        return std::make_shared<MultipleHitBlock>(position);
    }
    std::shared_ptr<Block> GlassBlockFactory::Create(const sf::Vector2f& position)
    {
        return std::make_shared<GlassBlock>(position);
    }
}
