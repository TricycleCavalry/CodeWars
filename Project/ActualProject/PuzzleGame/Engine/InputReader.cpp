#include "stdafx.h"
#include "InputReader.h"

#define HR( temp )

InputReader::InputReader(void)
:	myDirectInput(NULL)
,	myDIKeyboard(NULL)
,	myDIMouse(NULL)
{
}

InputReader::~InputReader(void)
{
	UnacquireMouse();
	UnacquireKeyboard();
	if(myDirectInput != NULL)
	{
		myDirectInput->Release();
		myDirectInput = NULL;
	}
}

bool InputReader::Init(HINSTANCE hInstance, HWND hWnd, int aScreenWidth, int aScreenHeight, bool anExclusiveFlag)
{
	myHWND = hWnd;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(myHWND, &p);
	myExclusiveFlag = anExclusiveFlag;

	myScreenWidth = aScreenWidth;
	myScreenHeight = aScreenHeight;

	myMousePos.x = static_cast<int>(p.x);
	myMousePos.y = static_cast<int>(p.y);

	HRESULT hr = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&myDirectInput, NULL);

	if(SetupKeyboard() == false)
		return false;
	if(SetupMouse() == false)
		return false;

	return true;
}

bool InputReader::Update()
{
	if(ReadKeyboard() == false)
		return false;
	if(ReadMouse() == false)
		return false;

	ProcessInput();

	return true;
}

void InputReader::ChangeScreenSize(int aScreenWidth, int aScreenHeight)
{
	myScreenWidth = aScreenWidth;
	myScreenHeight = aScreenHeight;
}

void InputReader::RecaptureKeyboard()
{
	while(SetupKeyboard() == false);
}

void InputReader::RecaptureMouse()
{
	while(SetupMouse() == false);
}

void InputReader::SetExclusiveAccess(const bool& anExclusiveFlag)
{
	myExclusiveFlag = anExclusiveFlag;
}

void InputReader::SetMousePos(const Vector2<int>& aPos)
{
	myMousePos = aPos;
}

InputData InputReader::GetData()
{
	InputData returnData;
	memcpy(&returnData.myKeyboardState,&myDIKeyboardState,sizeof(BYTE)*256);
	returnData.myMouseState = myDIMouseState;
	returnData.myMousePos = myMousePos;
	return returnData;
}

bool InputReader::SetupKeyboard()
{
	UnacquireKeyboard();

	HRESULT hr = myDirectInput->CreateDevice(GUID_SysKeyboard, &myDIKeyboard, NULL);

	hr = myDIKeyboard->SetDataFormat(&c_dfDIKeyboard);

	hr = myDIKeyboard->SetCooperativeLevel(myHWND, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	while(myDIKeyboard->Acquire() == false);

	return true;
}

bool InputReader::SetupMouse()
{
	UnacquireMouse();

	HRESULT hr = myDirectInput->CreateDevice(GUID_SysMouse, &myDIMouse, NULL);

	hr = myDIMouse->SetDataFormat(&c_dfDIMouse2);

	DWORD cooperativeFlags = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND;

	if(myExclusiveFlag == true)
	{
		cooperativeFlags = DISCL_FOREGROUND | DISCL_EXCLUSIVE;
	}
	hr = myDIMouse->SetCooperativeLevel(myHWND,cooperativeFlags);

	while(myDIMouse->Acquire() == false);

	return true;
}

void InputReader::UnacquireMouse()
{
	if(myDIMouse != NULL)
	{
		myDIMouse->Unacquire();
		myDIMouse->Release();
		myDIMouse = NULL;
	}
}

void InputReader::UnacquireKeyboard()
{
	if(myDIKeyboard != NULL)
	{
		myDIKeyboard->Unacquire();
		myDIKeyboard->Release();
		myDIKeyboard = NULL;
	}
}

bool InputReader::ReadKeyboard()
{
	HRESULT result;
	memset(&myDIKeyboardState,0,sizeof(myDIKeyboardState));
	result = myDIKeyboard->GetDeviceState(sizeof(myDIKeyboardState), reinterpret_cast<LPVOID>(&myDIKeyboardState));
	if(FAILED(result))
	{
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			myDIKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

bool InputReader::ReadMouse()
{
	HRESULT result;

	memset(&myDIMouseState,0,sizeof(myDIMouseState));
	result = myDIMouse->GetDeviceState(sizeof(myDIMouseState), reinterpret_cast<LPVOID>(&myDIMouseState));
	if(FAILED(result))
	{
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			myDIKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
	return true;
}

void InputReader::ProcessInput()
{
	if(myExclusiveFlag == true)
	{
		myMousePos.x += myDIMouseState.lX;
		myMousePos.y += myDIMouseState.lY;
	}
	else
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(myHWND,&p);
		myMousePos.x = static_cast<int>(p.x);
		myMousePos.y = static_cast<int>(p.y);
	}

	if(myDIMouseState.lZ > 0)
	{
		myDIMouseState.lZ = 1;
	}
	else if(myDIMouseState.lZ < 0)
	{
		myDIMouseState.lZ = -1;
	}

	if(myExclusiveFlag == true)
	{
		if(myMousePos.x < 0)
		{
			myMousePos.x = 0;
		}
		if(myMousePos.y < 0)
		{
			myMousePos.y = 0;
		}

		if(myMousePos.x > myScreenWidth)
		{
			myMousePos.x = myScreenWidth;
		}
		if(myMousePos.y > myScreenHeight)
		{
			myMousePos.y = myScreenHeight;
		}
	}
}