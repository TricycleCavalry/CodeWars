#include "SystemTime.h"

SystemTime::SystemTime(void)
:	myCurrentTime(SYSTEM_CLOCK,0)
,	myElapsedTime(SYSTEM_CLOCK,0)
,	myAttachedTimers(100)
{
}

SystemTime::~SystemTime(void)
{
}

void SystemTime::Init()
{
	myCurrentTime.SetTime(0);
	myElapsedTime.SetTime(0);

	myCallOverhead.QuadPart = 0;

	for(int i=0;i<1000;i++)
	{
		LARGE_INTEGER start;
		LARGE_INTEGER end;

		QueryPerformanceCounter(&start);
		QueryPerformanceCounter(&end);

		myCallOverhead.QuadPart += end.QuadPart - start.QuadPart;
	}

	myCallOverhead.QuadPart /= 1000;
	QueryPerformanceFrequency(&myPerformanceTimercalibrationData);

	QueryPerformanceCounter(&myClockStarted);
	myFrameStarted = myClockStarted;
}

const Time& SystemTime::GetTotalTime() const
{
	return myCurrentTime;
}

bool SystemTime::Update()
{
	LARGE_INTEGER updateTime;

	QueryPerformanceCounter(&updateTime);
	myClockStarted.QuadPart += myCallOverhead.QuadPart;

	double startTime = myCurrentTime.GetTime();

	double lastFrame = static_cast<double>(updateTime.QuadPart - myClockStarted.QuadPart);
	lastFrame /= static_cast<double>(myPerformanceTimercalibrationData.QuadPart);

	myCurrentTime.SetTime(lastFrame);

	myElapsedTime.SetTime(myCurrentTime.GetTime() - startTime);

	for(int i=0;i<myAttachedTimers.Count();i++)
	{
		myAttachedTimers[i]->Update(myElapsedTime);
	}

	QueryPerformanceCounter(&myFrameStarted);
	
	return true;
}

void SystemTime::AttachTimer(Timer* aTimer)
{
	myAttachedTimers.Add(aTimer);
}