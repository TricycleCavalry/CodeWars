#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

#include "TimeManager.h"
#include "InputHandler.h"
#include "Game.h"

class HGE;
class hgeFont;
class hgeSprite;

class App
{
public:
	App(HGE& aHGE);
	~App();

	bool Init();
	bool Destroy();
	bool Update();

	bool Render();
private:
	HGE& myHGE;
	TimeManager myTimeManager;

	Game myGame;
};

#endif