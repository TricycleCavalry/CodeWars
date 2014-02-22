#include "Timer.h"

Timer::Timer(Clocks aClock)
:	myIsPausedFlag(false)
,	myCurrentTime(aClock,0)
,	myElapsedTime(aClock,0)
,	myAttachedTimers(4)
{
}

Timer::~Timer(void)
{
}

void Timer::AttachTimer(Timer* aTimer)
{
	myAttachedTimers.Add(aTimer);
}

bool Timer::Update(Time& aElapsedTime)
{
	if(myIsPausedFlag == false)
	{
		myCurrentTime += aElapsedTime;
		myElapsedTime = aElapsedTime;
		for(int i=0;i<myAttachedTimers.Count();i++)
		{
			myAttachedTimers[i]->Update(aElapsedTime);
		}
	}
	else
	{
		myElapsedTime.SetTime(0);
		for(int i=0;i<myAttachedTimers.Count();i++)
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
