#ifndef _TIME_
#define _TIME_

enum Clocks
{
	SYSTEM_CLOCK,
	MASTER_CLOCK,
	SECONDARY_CLOCK,
	TERTIARY_CLOCK,
	GAME_CLOCK_01,
	GAME_CLOCK_02,
	GAME_CLOCK_03,
	GAME_CLOCK_04,
	GAME_CLOCK_05,
	GAME_CLOCK_06,
	GAME_CLOCK_07,
	GAME_CLOCK_08,
	GAME_CLOCK_09,
	GAME_CLOCK_10,
	GAME_CLOCK_11,
	GAME_CLOCK_12,
	GAME_CLOCK_13,
	GAME_CLOCK_14,
	GAME_CLOCK_15,
	NUM_CLOCKS,
	ANY_CLOCK
};

class Time
{
public:
	Time();
	Time(const Clocks aClock,const double aTime);
	Time(const Time& aTime);
	~Time();

	Time& operator=(const Time& aTime);
	Time& operator+=(const Time& aTime);

	double GetTime() const;
	const float& GetTimeFloat() const { return myTimeFloat; };
	Clocks GetClock() const;

	bool IsAfter(Time& aTime) const;
	bool IsBefore(Time& aTime) const;
	void Add(Time& aTime);

	void SetTime(const double aTime);
	void SetClock(const Clocks aClock);
private:
	Clocks myClock;
	double myTime;
	float myTimeFloat;
};

#endif