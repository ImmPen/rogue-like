#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "DelayedAction.h"
#include "IObserver.h"

namespace Arcanoid
{
	enum class BlockType
	{
		Usual,
		Animated,
		Unbreakable,
		MultipleHit,
		Glass
	};

	class Block : public GameObject, public ICollidable, public IObservable
	{
	protected:
		static int BlockTypeToColorNum(BlockType type);
		void OnHit(CollisionType type) override;
		int hitCount = 1;
		int hitDecrease = 1;
		int color;
		int score = 100;
	public:
		Block(const sf::Vector2f& position, const int color);
		virtual ~Block() override = default;

		void Update(float timeDelta) override;
		CollisionType GetCollision(std::shared_ptr<ICollidable> collidableObject) const override;
		sf::FloatRect GetRect() override { return GetSpriteRect(); }

		virtual BlockType GetType() { return BlockType::Usual; }
		virtual bool IsBroken() const;
		int GetScore();

		void ApplyEffect();
		void DenyEffect();
	};

	class SmoothDestroyableBlock : public Block, public IDelayedAction
	{
		using Super = Block;
	protected:
		void OnHit(CollisionType type) override;
	public:
		SmoothDestroyableBlock(const sf::Vector2f& position, const int color);
		SmoothDestroyableBlock(const sf::Vector2f& position);
		~SmoothDestroyableBlock() override = default;

		void Update(float deltaTime) override;
		CollisionType GetCollision(std::shared_ptr<ICollidable> collidableObject) const override;
		bool IsBroken() const override;
		virtual BlockType GetType() override { return BlockType::Animated; }

		void EachTickAction(float deltaTime) override;
		void UpdateTimer(float deltaTime) override;
	};

	class UnbreakableBlock : public Block
	{

	public:
		UnbreakableBlock(const sf::Vector2f& position);
		~UnbreakableBlock() override = default;

		virtual BlockType GetType() override { return BlockType::Unbreakable; }
	};
}
