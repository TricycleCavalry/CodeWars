#ifndef _DIRECT_INPUT_HEADER_
#define _DIRECT_INPUT_HEADER_

#ifndef _DIRECT_INPUT_
#define _DIRECT_INPUT_

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#endif


#include "GrowingArray.h"
#include "Vector2.h"
#include "InputData.h"
#include "StaticArray.h"


class InputReader
{
public:
	InputReader(void);
	~InputReader(void);

	bool Init(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight, bool aCaptureMouseFlag);
	void Destroy();

	bool Update();

	void ChangeScreenSize(const int& aScreenWidth, const int& aScreenHeight);

	void ReCaptureMouse(HWND aHWND);
	void ReCaptureKeyBoard(HWND aHWND);

	void SetExclusiveFlag(const bool& anExclusiveFlag);

	InputData GetData();

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

	LPDIRECTINPUT8 myDirectInput;
	LPDIRECTINPUTDEVICE8 myDIKeyboard;
	LPDIRECTINPUTDEVICE8 myDIMouse;

	int myScreenWidth;
	int myScreenHeight;
	int myOriginalScreenWidth;
	int myOriginalScreenHeight;

	BYTE myDIKeyboardState[256];
	DIMOUSESTATE2 myDIMouseState;
	Vector2<int> myMousePos;

	HWND myHWnd;

	bool myCaptureMouseFlag;
};

#endif