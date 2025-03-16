#pragma once
#include "Bonus.h"
#include "IObserver.h"
#include <memory>
#include <set>

namespace Arcanoid
{
	class BonusState : public IObservable
	{
	public:
		BonusState() = default;
		virtual ~BonusState() = default;
		virtual void Update(float deltaTime);
		virtual std::set<BonusType> GetBonus() { return std::set<BonusType>{ BonusType::NoBonus }; }
	protected:
		float timer = 10.f;
		bool isActive = true;
	};

	class BonusDecorator : public BonusState
	{
		using Super = BonusState;
	public:
		BonusDecorator(std::shared_ptr<BonusState> bonus)
			: bonusState(bonus)
		{}
		virtual void Update(float deltaTime) override;
		virtual std::set<BonusType> GetBonus() override;
	protected:
		std::shared_ptr<BonusState> bonusState;
	};

	class OnBallDecorator : public BonusDecorator
	{
		using Super = BonusState;
	public:
		OnBallDecorator(std::shared_ptr<BonusState> bonus) : BonusDecorator(bonus)
		{}
		virtual void Update(float deltaTime) override;
		virtual std::set<BonusType> GetBonus() override;
	};

	class OnBlockDecorator : public BonusDecorator
	{
		using Super = BonusState;
	public:
		OnBlockDecorator(std::shared_ptr<BonusState> bonus)	: BonusDecorator(bonus)
		{}
		virtual void Update(float deltaTime) override;
		virtual std::set<BonusType> GetBonus() override;
	};

	class OnPlatformDecorator : public BonusDecorator
	{
		using Super = BonusState;
	public:
		OnPlatformDecorator(std::shared_ptr<BonusState> bonus) : BonusDecorator(bonus)
		{}
		virtual void Update(float deltaTime) override;
		virtual std::set<BonusType> GetBonus() override;
	};
}
