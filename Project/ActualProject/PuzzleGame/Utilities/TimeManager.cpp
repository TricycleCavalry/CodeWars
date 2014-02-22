#include "Windows.h"
#include "TimeManager.h"
#include "assert.h"

#include <iostream>

TimeManager::TimeManager(void)
{
	myClocks.Init(NUM_CLOCKS);
	InitDefaults();
}

TimeManager::~TimeManager(void)
{
}

void TimeManager::InitDefaults()
{
	mySystemClock = NULL;
	for(int i=0;i<NUM_CLOCKS;i++)
	{
		myClocks.Add(NULL);
	}
	CreateTimer(SYSTEM_CLOCK);
	mySystemClock->Init();
	CreateTimer(MASTER_CLOCK);
	mySystemClock->AttachTimer(myClocks[MASTER_CLOCK]);
	myDefaultClock = MASTER_CLOCK;
}

bool TimeManager::Update()
{
	mySystemClock->Update();
	return true;
}

void TimeManager::CreateTimer(const Clocks aTimer)
{
	if(aTimer == SYSTEM_CLOCK)
	{
		if(mySystemClock == NULL)
		{
			mySystemClock = new SystemTime;
		}
	}
	else
	{
		if(myClocks[aTimer] == NULL)
		{
			myClocks[aTimer] = new Timer;
		}
	}
}

bool TimeManager::AttachTimerToTimer(const Clocks aTimerToAttachTo, const Clocks aTimerToAttach)
{
	assert(aTimerToAttach != SYSTEM_CLOCK);
	myClocks[aTimerToAttachTo]->AttachTimer(myClocks[aTimerToAttach]);
	return true;
}

const Time& TimeManager::GetElapsedTime() const
{
	return myClocks[myDefaultClock]->GetElapsedTime();
}

const Time& TimeManager::GetTotalTime() const
{
	return myClocks[myDefaultClock]->GetTotalTime();
}


const Time& TimeManager::GetElapsedTime(const Clocks aTimer) const
{
	assert(aTimer != SYSTEM_CLOCK);
	return myClocks[aTimer]->GetElapsedTime();
}

const Time& TimeManager::GetTotalTime(const Clocks aTimer) const
{
	assert(aTimer != SYSTEM_CLOCK);
	return myClocks[aTimer]->GetTotalTime();
}

bool TimeManager::SetClockPauseState(const Clocks aTimer, const bool aPauseState)
{
	assert(aTimer != SYSTEM_CLOCK);
	myClocks[aTimer]->SetPauseState(aPauseState);
	return true;
}

void TimeManager::SetCurrentDefaultClock(const Clocks aTimer)
{
	myDefaultClock = aTimer;
}

TimeManager& TimeManager::operator=(const TimeManager& aTimeManager)
{
	myDefaultClock = aTimeManager.myDefaultClock;
	myClocks = aTimeManager.myClocks;
	mySystemClock = aTimeManager.mySystemClock;
	return *this;
}