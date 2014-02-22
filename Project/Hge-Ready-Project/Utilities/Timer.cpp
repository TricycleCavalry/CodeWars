#include "Timer.h"

Timer::Timer(Clocks aClock)
:	myIsPausedFlag(false),
myCurrentTime(aClock,0),
myElapsedTime(aClock,0)
{
}

Timer::~Timer(void)
{
}

void Timer::AttachTimer(Timer* aTimer)
{
	myAttachedTimers.push_back(aTimer);
}

bool Timer::Update(Time& aElapsedTime)
{
	if(myIsPausedFlag == false)
	{
		myCurrentTime += aElapsedTime;
		myElapsedTime = aElapsedTime;
		for(unsigned int i=0;i<myAttachedTimers.size();i++)
		{
			myAttachedTimers[i]->Update(aElapsedTime);
		}
	}
	else
	{
		myElapsedTime.SetTime(0);
		for(unsigned int i=0;i<myAttachedTimers.size();i++)
		{
			myAttachedTimers[i]->Update(myElapsedTime);
		}
	}
	return true;
}

void Timer::SetPauseState(bool aPausedFlag)
{
	myIsPausedFlag = aPausedFlag;
}

const Time& Timer::GetTotalTime() const
{
	return myCurrentTime;
}

const Time& Timer::GetElapsedTime() const
{
	return myElapsedTime;
}
