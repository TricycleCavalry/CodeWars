#ifndef _TIME_MANAGER_
#define _TIME_MANAGER_

#include "GrowingArray.h"
#include "SystemTime.h"

class Timer;
class SystemTime;

class TimeManager
{
public:
	TimeManager();
	~TimeManager();
	
	void InitDefaults();

	bool Update();

	void CreateTimer(const Clocks aTimer);
	bool AttachTimerToTimer(const Clocks aTimerToAttachTo,const Clocks aTimerToAttach);

	const Time& GetElapsedTime() const;
	const Time& GetTotalTime() const;

	const Time& GetElapsedTime(const Clocks aTimer) const;
	const Time& GetTotalTime(const Clocks aTimer) const;
	bool SetClockPauseState(const Clocks aTimer,const bool aPauseState);

	void SetCurrentDefaultClock(const Clocks aTimer);

	TimeManager& operator=(const TimeManager& aTimeManager);
	
private:
	Clocks myDefaultClock;
	GrowingArray<Timer*> myClocks;
	SystemTime* mySystemClock;
};
#endif