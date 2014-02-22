#ifndef _TIMER_
#define _TIMER_

#include "TI_Time.h"
#include <vector>

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
	std::vector<Timer*> myAttachedTimers;
	Time myCurrentTime;
	Time myElapsedTime;
};

#endif