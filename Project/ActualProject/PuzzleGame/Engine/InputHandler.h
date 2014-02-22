#ifndef _INPUT_HANDLER_HEADER_
#define _INPUT_HANDLER_HEADER_

#include "InputReader.h"
#include <bitset>

#define InputKeyState(aKey, aKeyState) InputHandler::GetInstance()->KeyState(aKey,aKeyState)
#define InputMouseState(aKey, aKeyState) InputHandler::GetInstance()->MouseKeyState(aKey,aKeyState)
#define InputGetMousePos() InputHandler::GetInstance()->GetMousePos()
#define InputGetMouseMovement() InputHandler::GetInstance()->GetMouseMovement()
#define InputGetMousePos3DRelative() InputHandler::GetInstance()->GetMousePosition3DRelative()
#define InputGetMousePositionFromCenter()  InputHandler::GetInstance()->GetMousePositionFromCenter()
#define InputGetKeyboardState() InputHandler::GetInstance()->GetKeyboardState();
#define InputGetMouseState() InputHandler::GetInstance()->GetMouseState();
enum : unsigned int
{
	DIK_LMB = 256,
	DIK_RMB,
	DIK_MMB,
};

enum DIKeyState
{
	DIKS_UP,
	DIKS_DOWN,
	DIKS_CLICKED,
	DIKS_PRESSED,
	DIKS_RELEASED,
};

class InputHandler
{
public:
	InputHandler(void);
	~InputHandler(void);

	static void Create(HINSTANCE hInstance, HWND hWnd, int aScreenWidth, int aScreenHeight, bool anExclusiveFlag);
	static void Destroy();
	static InputHandler* GetInstance();

	bool Init(HINSTANCE hInstance, HWND hWnd, int aScreenWidth, int aScreenHeight, bool anExclusiveFlag);

	void Update();

	void OnResize(int aScreenWidth, int aScreenHeight);

	void RecaptureDevices();
	void SetExclusiveAccess(const bool& anExclusiveFlag);

	//void 

	bool KeyState(const BYTE& aKey, const DIKeyState& aKeyState);
	BYTE GetClickedKey();
	bool MouseKeyState(const BYTE& aKey, const DIKeyState& aKeyState);

	Vector2<float> GetMousePos() const;
	void SetMousePos(const Vector2<int>& aPos);

	Vector2<float> GetMouseMovement() const;

	Vector2<float> GetMousePositionFromCenter() const;
	
	Vector2<float> GetMousePosition3DRelative() const;

	std::bitset<256> GetKeyboardState();
	std::bitset<8> GetMouseState();

private:

	bool IsKeyPressed(const BYTE& aKey);
	bool IsKeyClicked(const BYTE& aKey);
	bool IsKeyReleased(const BYTE& aKey);

	bool IsMousePressed(const BYTE& aKey);
	bool IsMouseClicked(const BYTE& aKey);
	bool IsMouseReleased(const BYTE& aKey);

	InputReader myInputReader;
	
	BYTE myKeyboardState[256];
	std::bitset<256> myKeyboardclicks;
	std::bitset<256> myPreviousKeyboardClicks;

	DIMOUSESTATE2 myMouseState;
	Vector2<int> myMousePos;
	std::bitset<8> myMouseClicks;
	std::bitset<8> myPreviousMouseClicks;

	Vector2<int> myScreenResolution;

	static InputHandler* ourInstance;
};

#endif