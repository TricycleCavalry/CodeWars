#ifndef _SYSTEM_TIME_
#define _SYSTEM_TIME_

#include "Timer.h"
#include "Windows.h"
#include <vector>

class Timer;

class SystemTime
{
public:
	SystemTime(void);
	~SystemTime(void);

	void Init();

	void AttachTimer(Timer* aTimer);

	bool Update();

	const Time& GetTotalTime() const;
	const Time& GetElapsedTime() const;
private:
	std::vector<Timer*> myAttachedTimers;
	Time myCurrentTime;
	Time myElapsedTime;

	LARGE_INTEGER myPerformanceTimercalibrationData;
	LARGE_INTEGER myClockStarted;
	LARGE_INTEGER myFrameStarted;
	LARGE_INTEGER myCallOverhead;
};

#endif