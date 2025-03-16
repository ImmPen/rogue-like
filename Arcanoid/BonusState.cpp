#include "BonusState.h"

namespace Arcanoid
{
	void BonusState::Update(float delta)
	{
		if (isActive)
		{
			timer -= delta;
			if (timer < 0)
			{
				isActive = !isActive;
				Emit();
			}
		}
	}
	void BonusDecorator::Update(float deltaTime)
	{
		bonusState->Update(deltaTime);
		Super::Update(deltaTime);
	}
	std::set<BonusType> BonusDecorator::GetBonus()
	{
		auto bonuses = bonusState->GetBonus();
		if (isActive)
		{
			return bonuses;
		}
		return std::set<BonusType>();
	}
	void OnBallDecorator::Update(float deltaTime)
	{
		bonusState->Update(deltaTime);
		Super::Update(deltaTime);
	}
	std::set<BonusType> OnBallDecorator::GetBonus()
	{
		auto bonuses = bonusState->GetBonus();
		if (isActive)
		{
			bonuses.insert(BonusType::OnBallBonus);
		}
		return bonuses;
	}
	void OnBlockDecorator::Update(float deltaTime)
	{
		bonusState->Update(deltaTime);
		Super::Update(deltaTime);
	}
	std::set<BonusType> OnBlockDecorator::GetBonus()
	{
		auto bonuses = bonusState->GetBonus();
		if (isActive)
		{
			bonuses.insert(BonusType::OnBlockBonus);
		}
		return bonuses;
	}
	void OnPlatformDecorator::Update(float deltaTime)
	{
		bonusState->Update(deltaTime);
		Super::Update(deltaTime);
	}
	std::set<BonusType> OnPlatformDecorator::GetBonus()
	{
		auto bonuses = bonusState->GetBonus();
		if (isActive)
		{
			bonuses.insert(BonusType::OnPlatformBonus);
		}
		return bonuses;
	}
}