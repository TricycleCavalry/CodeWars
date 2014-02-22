#ifndef APPLICATION_HEADER
#define APPLICATION_HEADER

class HGE;
class hgeFont;
class hgeSprite;
class Engine;

#include "StateStack.h"

class App
{
public:
	App();
	~App();

	void Init();
	void Start();
private:
	
	Engine* myEngine;
	StateStack myStateStack;
};

#endif