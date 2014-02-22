#ifndef _INPUT_HANDLER_HEADER_
#define _INPUT_HANDLER_HEADER_

#include "InputData.h"
#include "Vector2.h"
#include <bitset>

#define LMB 0
#define RMB 1
#define MMB 2

enum INPUT_CLICKS
{
	IS_NOT_CLICKED,
	IS_CLICKED,
};

class Camera;

class InputHandler
{
public:
	InputHandler(void);
	~InputHandler(void);

	void Update(const InputData& anInputUpdate);

	bool IsKeyPressed(BYTE aKey);
	bool IsKeyClicked(BYTE aKey);

	int GetClickedKey();

	bool IsMouseButtonPressed(BYTE aButton);
	bool IsMouseButtonClicked(BYTE aButton);

	int GetMouseWheelChange();

	Vector2<float> GetMousePos();

	void SetKeyState(BYTE aKey, const bool& aBoolFlag);
	void SetMouseButtonState(BYTE aButton, const bool& aBoolFlag);
	void SetMousePos(const Vector2<float>& aNewPos);

	DIMOUSESTATE2 GetMouseState() { return myMouseState; }

private:

	BYTE myKeyboardState[256];
	std::bitset<256> myKeyboardClicks;
	std::bitset<256> myPreviousKeyBoardClicks;

	DIMOUSESTATE2 myMouseState;
	Vector2<int> myMousePos;
	std::bitset<8> myMouseClicks;
	std::bitset<8> myPreviousMouseClicks;
};

#endif