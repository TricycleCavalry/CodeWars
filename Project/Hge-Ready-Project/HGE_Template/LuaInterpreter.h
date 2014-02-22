#ifndef _LUA_INTERPRETER_HEADER_
#define _LUA_INTERPRETER_HEADER_

#include <string>
#include "GrowingArray.h"

class LuaState;
class InputHandler;
class Font;

class LuaInterpreter
{
public:
	LuaInterpreter(InputHandler* anInputHandler);
	~LuaInterpreter(void);

	void Update(const float& anElapsedTime);

	void Render();

	bool IsOn() const;
private:

	void HandleInput();

	InputHandler* myInputHandler;
	LuaState* myLuaState;

	GrowingArray<std::string> myOldStrings;
	std::string myEnteredString;

	Font* myFont;

	bool myIsSwitchedOn;

	float myTextPositionIndicatorTimer;
};

#endif