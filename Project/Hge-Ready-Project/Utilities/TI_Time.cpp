#include "TI_Time.h"

Time::Time(void)
:	myTime(0),
	myClock(ANY_CLOCK)
{
}

Time::Time(const Clocks aClock, const double aTime)
:	myClock(aClock),
	myTime(aTime)
{
}

Time::Time(const Time& aTime)
:	myTime(aTime.GetTime()),
myClock(aTime.GetClock())
{
}

Time::~Time(void)
{
}

double Time::GetTime() const
{
	return myTime;
}

Clocks Time::GetClock() const
{
	return myClock;
}

void Time::Add(Time &aTime)
{
	myTime += aTime.GetTime();
}

void Time::SetTime(const double aTime)
{
	myTime = aTime;
}

void Time::SetClock(const Clocks aClock)
{
	myClock = aClock;
}

Time& Time::operator =(const Time &aTime)
{
	myTime = aTime.GetTime();
	myClock = aTime.GetClock();
	return *this;
}

Time& Time::operator +=(const Time &aTime)
{
	myTime += aTime.GetTime();
	return *this;
}