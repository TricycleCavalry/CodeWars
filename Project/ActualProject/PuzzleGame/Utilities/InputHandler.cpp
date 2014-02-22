#include "InputHandler.h"
//#include "DL_Debug.h"
#include "Vector2.h"

InputHandler* InputHandler::ourInstance = NULL;

InputHandler::InputHandler(void)
{
	memset(&myKeyboardState,0,sizeof(myKeyboardState));
	memset(&myMouseState,0,sizeof(myMouseState));
	myKeyboardclicks.reset();
	myPreviousKeyboardClicks.reset();
	myMouseClicks.reset();
	myPreviousMouseClicks.reset();
	myMousePos = Vector2<int>(0,0);
}

InputHandler::~InputHandler(void)
{
}

void InputHandler::Create(HINSTANCE hInstance, HWND hWnd, int aScreenWidth, int aScreenHeight, bool anExclusiveFlag)
{
	if(ourInstance != NULL)
	{
		//DL_ASSERT("Instance of InputHandler already exists.");
	}

	ourInstance = new InputHandler();
	ourInstance->Init(hInstance,hWnd,aScreenWidth,aScreenHeight,anExclusiveFlag);
}

void InputHandler::Destroy()
{
	if(ourInstance == NULL)
	{
		//DL_ASSERT("Instance of InputHandler does not exist.");
	}
	ourInstance->~InputHandler();
}

InputHandler* InputHandler::GetInstance()
{
	return ourInstance;
}

bool InputHandler::Init(HINSTANCE hInstance, HWND hWnd, int aScreenWidth, int aScreenHeight, bool anExclusiveFlag)
{
	myScreenResolution = Vector2<int>(aScreenWidth,aScreenHeight);
	return myInputReader.Init(hInstance,hWnd,aScreenWidth,aScreenHeight,anExclusiveFlag);
}

void InputHandler::Update()
{
	myInputReader.Update();
	InputData inputData = myInputReader.GetData();
	
	memcpy(myKeyboardState,inputData.myKeyboardState,sizeof(myKeyboardState));
	myMouseState = inputData.myMouseState;
	myMousePos = inputData.myMousePos;

	myPreviousKeyboardClicks = myKeyboardclicks;
	myKeyboardclicks.reset();
	myPreviousMouseClicks = myMouseClicks;
	myMouseClicks.reset();
}

void InputHandler::OnResize(int aScreenWidth, int aScreenHeight)
{
	myScreenResolution.myX = aScreenWidth;
	myScreenResolution.myY = aScreenHeight;
	myInputReader.ChangeScreenSize(aScreenWidth,aScreenHeight);
}

void InputHandler::RecaptureDevices()
{
	if(ourInstance != NULL)
	{
		myInputReader.RecaptureKeyboard();
		myInputReader.RecaptureMouse();
	}
}

void InputHandler::SetExclusiveAccess(const bool& anExclusiveFlag)
{
	myInputReader.SetExclusiveAccess(anExclusiveFlag);
}

bool InputHandler::KeyState(const BYTE& aKey, const DIKeyState& aKeyState)
{
	switch(aKeyState)
	{
	case DIKS_CLICKED:
		return IsKeyClicked(aKey);
	case DIKS_PRESSED:
		return IsKeyPressed(aKey);
	case DIKS_RELEASED:
		return IsKeyReleased(aKey);
	}
	//DL_ASSERT("KeyState does not exist!");
	return false;
}

BYTE InputHandler::GetClickedKey()
{
	for(int i=0;i<256;i++)
	{
		if(IsKeyClicked(i) == true)
		{
			return static_cast<BYTE>(i);
		}
	}
	return static_cast<BYTE>(0);
}

bool InputHandler::MouseKeyState(const BYTE& aKey, const DIKeyState& aKeyState)
{
	switch(aKeyState)
	{
	case DIKS_CLICKED:
		return IsMouseClicked(aKey);
	case DIKS_PRESSED:
		return IsMousePressed(aKey);
	case DIKS_RELEASED:
		return IsMouseReleased(aKey);
	}
	//DL_ASSERT("KeyState does not exist!");
	return false;
}

Vector2<float> InputHandler::GetMousePos() const
{
	return Vector2<float>(static_cast<float>(myMousePos.x),static_cast<float>(myMousePos.y));
}

void InputHandler::SetMousePos(const Vector2<int>& aPos)
{
	myInputReader.SetMousePos(aPos);
}

Vector2<float> InputHandler::GetMouseMovement() const
{
	return Vector2<float>(static_cast<float>(myMouseState.lX),static_cast<float>(myMouseState.lY));
}
Vector2<float> InputHandler::GetMousePositionFromCenter() const
{
	//return   GetMousePos() - (Vector2<float>(static_cast<float>(myScreenResolution.x)*0.5f,static_cast<float>(myScreenResolution.y)/2));

	float halfWidth = static_cast<float>(myScreenResolution.x)*0.5f;
	float halfHeight = static_cast<float>(myScreenResolution.y)*0.5f;
	Vector2f returnPos = GetMousePos() - (Vector2<float>(halfWidth,halfHeight));
	returnPos.myX /= halfWidth;
	returnPos.myY /= halfHeight;

	return returnPos;
}

Vector2<float> InputHandler::GetMousePosition3DRelative() const
{
	float halfWidth = static_cast<float>(myScreenResolution.x)*0.5f;
	float halfHeight = static_cast<float>(myScreenResolution.y)*0.5f;
	Vector2f returnPos = GetMousePos() - (Vector2<float>(halfWidth,halfHeight));
	returnPos.y = -returnPos.y;

	return returnPos;
}

std::bitset<256> InputHandler::GetKeyboardState()
{
	std::bitset<256> returnBits;
	for(int i = 0; i < 256; ++i)
	{
		returnBits.set(i,(myKeyboardState[i] & 0x80) == 1);
	}
	return returnBits;
	
}
std::bitset<8> InputHandler::GetMouseState()
{
	std::bitset<8> returnBits;
	for(int i = 0; i < 8; ++i)
	{
		returnBits.set(i,(myMouseState.rgbButtons[i] == 1));
	}
	return returnBits;
}
bool InputHandler::IsKeyPressed(const BYTE& aKey)
{
	if(myKeyboardState[aKey] & 0x80)
	{
		myKeyboardclicks[aKey] = DIKS_DOWN;
		return true;
	}
	return false;
}

bool InputHandler::IsKeyClicked(const BYTE& aKey)
{
	if(myKeyboardState[aKey] & 0x80)
	{
		myKeyboardclicks[aKey] = DIKS_DOWN;
		if(myPreviousKeyboardClicks[aKey] == DIKS_UP)
		{
			return true;
		}
	}
	return false;
}

bool InputHandler::IsKeyReleased(const BYTE& aKey)
{
	if(!(myKeyboardState[aKey] & 0x80))
	{
		if(myPreviousKeyboardClicks[aKey] == DIKS_DOWN)
		{
			return true;
		}
	}
	else
	{
		myKeyboardclicks[aKey] = DIKS_DOWN;
	}
	return false;
}

bool InputHandler::IsMousePressed(const BYTE& aKey)
{
	if(myMouseState.rgbButtons[aKey])
	{
		myMouseClicks[aKey] = DIKS_DOWN;
		return true;
	}
	return false;
}

bool InputHandler::IsMouseClicked(const BYTE& aKey)
{
	if(myMouseState.rgbButtons[aKey])
	{
		myMouseClicks[aKey] = DIKS_DOWN;
		if(myPreviousMouseClicks[aKey] == DIKS_UP)
		{
			return true;
		}
	}
	return false;
}

bool InputHandler::IsMouseReleased(const BYTE& aKey)
{
	if(!(myMouseState.rgbButtons[aKey]))
	{
		if(myPreviousMouseClicks[aKey] == DIKS_DOWN)
		{
			return true;
		}
	}
	else
	{
		myMouseClicks[aKey] = DIKS_DOWN;
	}
	return false;
}