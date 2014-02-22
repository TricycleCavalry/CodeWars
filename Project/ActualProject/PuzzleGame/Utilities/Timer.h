#ifndef _TIMER_
#define _TIMER_

#include "GrowingArray.h"
#include "TI_Time.h"

class Timer
{
public:
	Timer(Clocks aClock=MASTER_CLOCK);
	~Timer(void);

	void AttachTimer(Timer* aTimer);

	bool Update(Time& aElapsedTime);
	void SetPauseState(bool aPausedFlag);

	const Time& GetTotalTime() const;
	const Time& GetElapsedTime() const;
private:
	bool myIsPausedFlag;
	GrowingArray<Timer*> myAttachedTimers;
	Time myCurrentTime;
	Time myElapsedTime;
};

#endif