#ifndef _INPUT_READER_HEADER_
#define _INPUT_READER_HEADER_

#ifndef _DIRECT_INPUT_
#define _DIRECT_INPUT_

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#endif

#include "InputData.h"

class InputReader
{
public:
	InputReader(void);
	~InputReader(void);

	bool Init(HINSTANCE hInstance, HWND hWnd, int aScreenWidth, int aScreenHeight, bool anExclusiveFlag);
	void Destroy();

	bool Update();

	void ChangeScreenSize(int aScreenWidth, int aScreenHeight);

	void RecaptureKeyboard();
	void RecaptureMouse();

	void SetExclusiveAccess(const bool& anExclusiveFlag);

	void SetMousePos(const Vector2<int>& aPos);

	InputData GetData();

private:
	bool SetupKeyboard();
	bool SetupMouse();

	void UnacquireMouse();
	void UnacquireKeyboard();

	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

	LPDIRECTINPUT8 myDirectInput;
	LPDIRECTINPUTDEVICE8 myDIKeyboard;
	LPDIRECTINPUTDEVICE8 myDIMouse;

	int myScreenWidth;
	int myScreenHeight;

	BYTE myDIKeyboardState[256];
	DIMOUSESTATE2 myDIMouseState;
	Vector2<int> myMousePos;

	HWND myHWND;

	bool myExclusiveFlag;
};

#endif