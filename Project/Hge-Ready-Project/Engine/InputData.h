#ifndef _INPUT_DATA_HEADER_
#define _INPUT_DATA_HEADER_

#ifndef _DIRECT_INPUT_
#define _DIRECT_INPUT_

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#endif

#include "Vector2.h"

struct InputData
{
	BYTE myKeyboardState[256];
	DIMOUSESTATE2 myMouseState;
	Vector2<int> myMousePos;
};

#endif