#ifndef _TICKER_H_
#define _TICKER_H_

class Ticker
{
public:
	Ticker(void);
	~Ticker(void);

	void Init(int aTickFps = 60);	// aTickFps is the number of ticks per second
	void Update(const float& anElapsedTime);

	bool WillTick();	//Does not reduce myElapsedTime
	bool Tick();		//Reduces myElapsedTime
	float GetTickTime();
	void SetTickTime(float aTickTime){myTickTime=aTickTime;}
	void Clear(){myElapsedTime = 0.f;};
	void Set(float anElapsedTime){myElapsedTime=anElapsedTime;}

private:
	float myElapsedTime;
	float myTickTime;
};

#endif