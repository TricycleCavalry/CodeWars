#include "TI_Time.h"

Time::Time(void)
:	myTime(0),
	myClock(ANY_CLOCK)
{
}

Time::Time(const Clocks aClock, const double aTime)
:	myClock(aClock),
	myTime(aTime),
	myTimeFloat(static_cast<float>(aTime))
{
}

Time::Time(const Time& aTime)
:	myTime(aTime.GetTime()),
myClock(aTime.GetClock()),
myTimeFloat(static_cast<float>(myTime))
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
	myTimeFloat = static_cast<float>(myTime);
}

void Time::SetTime(const double aTime)
{
	myTime = aTime;
	myTimeFloat = static_cast<float>(myTime);
}

void Time::SetClock(const Clocks aClock)
{
	myClock = aClock;
}

Time& Time::operator =(const Time &aTime)
{
	myTime = aTime.GetTime();
	myTimeFloat = static_cast<float>(myTime);
	myClock = aTime.GetClock();
	return *this;
}

Time& Time::operator +=(const Time &aTime)
{
	myTime += aTime.GetTime();
	myTimeFloat = static_cast<float>(myTime);
	return *this;
}