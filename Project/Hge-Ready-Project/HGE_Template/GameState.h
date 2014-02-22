#ifndef _GAME_STATE_HEADER_
#define _GAME_STATE_HEADER_

#include "State.h"
#include "Vector2.h"
#include "CollisionSystem.h"

class InputHandler;
class LuaInterpreter;
class Entity;

class GameState : public State
{
public:
	GameState(StateStack& aStateStack, Engine* anEngine);
	~GameState(void);

	void Init();

	int Update();

	void Render();
private:
	InputHandler* myInputHandler;

	LuaInterpreter* myLuaInterpreter;
};

#endif