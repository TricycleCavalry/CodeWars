#include "Ticker.h"


Ticker::Ticker(void)
: myElapsedTime(0.f)
{
}


Ticker::~Ticker(void)
{
}
void Ticker::Init(int aTickFps)
{
	myTickTime = 1/static_cast<float>(aTickFps);
	myElapsedTime = 0;
}
void Ticker::Update(const float& anElapsedTime)
{
	myElapsedTime += anElapsedTime;
}
bool Ticker::WillTick()
{
	return (myElapsedTime >= myTickTime);
}
bool Ticker::Tick()
{
	if(myElapsedTime >= myTickTime)
	{
		myElapsedTime -= myTickTime;
		return true;
	}
	return false;
}
float Ticker::GetTickTime()
{
	return myTickTime;
}
