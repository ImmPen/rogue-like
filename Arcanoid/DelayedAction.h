#pragma once
namespace Arcanoid
{
	class IDelayedAction
	{
	protected:
		bool isTimerStarted = false;
		bool isTimerEnded = false;
		float currentTime;
		float destroyTime;

		virtual void UpdateTimer(float deltaTime)
		{
			if (!isTimerStarted || isTimerEnded)
			{
				return;
			}
			currentTime -= deltaTime;
			EachTickAction(deltaTime);
			if (currentTime <= 0)
			{
				isTimerEnded = true;
			}
		}

		virtual void EachTickAction(float deltaTime) = 0;
	public:
		void StartTimer(float destroyTime) 
		{
			this->destroyTime = destroyTime;
			this->currentTime = destroyTime;
			this->isTimerStarted = true;
		}
	};
}