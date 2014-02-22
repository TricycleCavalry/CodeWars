#include "stdafx.h"
#include "InputReader.h"

InputReader::InputReader(void)
{
	myDirectInput = NULL;
	myDIMouse = NULL;
	myDIKeyboard = NULL;
}

InputReader::~InputReader(void)
{
}

bool InputReader::Init(HINSTANCE hinstance, HWND hwnd, int aScreenWidth, int aScreenHeight, bool aCaptureMouseFlag)
{
	myHWnd = hwnd;
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnd,&p);
	myCaptureMouseFlag = aCaptureMouseFlag;
	myScreenWidth = myOriginalScreenWidth = aScreenWidth;
	myScreenHeight = myOriginalScreenHeight = aScreenHeight;
	myMousePos.x = static_cast<int>(p.x);
	myMousePos.y = static_cast<int>(p.y);
	HRESULT result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&myDirectInput, NULL);
	if(FAILED(result))
	{
		return false;
	}

	result = myDirectInput->CreateDevice(GUID_SysKeyboard, &myDIKeyboard, NULL);
	if(FAILED(result))
	{
		return false;
	}

	result = myDIKeyboard->SetDataFormat( &c_dfDIKeyboard);
	if(FAILED(result))
	{
		return false;
	}

	result = myDIKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result))
	{
		return false;
	}

	result = myDIKeyboard->Acquire();
	if(FAILED(result))
	{
		return false;
	}

	result = myDirectInput->CreateDevice(GUID_SysMouse, &myDIMouse, NULL);
	if(FAILED(result))
	{
		return false;
	}

	result = myDIMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(result))
	{
		return false;
	}

	if(aCaptureMouseFlag == true)
	{
		result = myDIMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	}
	else
	{
		result = myDIMouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
		ShowCursor(false);
	}
	if(FAILED(result))
	{
		return false;
	}

	result = myDIMouse->Acquire();
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void InputReader::Destroy()
{
	if(myDIMouse)
	{
		myDIMouse->Unacquire();
		myDIMouse->Release();
		myDIMouse = NULL;
	}

	if(myDIKeyboard)
	{
		myDIKeyboard->Unacquire();
		myDIKeyboard->Release();
		myDIKeyboard = NULL;
	}

	if(myDirectInput)
	{
		myDirectInput->Release();
		myDirectInput = NULL;
	}
}

bool InputReader::Update()
{
	bool result;

	result = ReadKeyboard();
	if(result == false)
	{
		return false;
	}

	result = ReadMouse();
	if(result == false)
	{
		return false;
	}
	
	ProcessInput();

	return true;
}

void InputReader::ChangeScreenSize(const int& aScreenWidth, const int& aScreenHeight)
{
	myScreenHeight = aScreenHeight;
	myScreenWidth = aScreenWidth;
}

void InputReader::ReCaptureMouse(HWND aHWND)
{
	myHWnd = aHWND;
	HRESULT result = myDirectInput->CreateDevice(GUID_SysMouse, &myDIMouse, NULL);
	if(FAILED(result))
	{
		return;
	}

	result = myDIMouse->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(result))
	{
		return;
	}

	if(myCaptureMouseFlag == true)
	{
		result = myDIMouse->SetCooperativeLevel(aHWND, DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY);
	}
	else
	{
		result = myDIMouse->SetCooperativeLevel(aHWND, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND | DISCL_NOWINKEY);
		ShowCursor(false);
	}
	if(FAILED(result))
	{
		return;
	}

	result = myDIMouse->Acquire();
	if(FAILED(result))
	{
		return;
	}
}

void InputReader::ReCaptureKeyBoard(HWND aHWND)
{
	myHWnd = aHWND;
	HRESULT result = myDirectInput->CreateDevice(GUID_SysKeyboard, &myDIKeyboard, NULL);
	if(FAILED(result))
	{
		return;
	}

	result = myDIKeyboard->SetDataFormat( &c_dfDIKeyboard);
	if(FAILED(result))
	{
		return;
	}

	result = myDIKeyboard->SetCooperativeLevel(aHWND, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result))
	{
		return;
	}

	result = myDIKeyboard->Acquire();
	if(FAILED(result))
	{
		return;
	}
}

void InputReader::SetExclusiveFlag(const bool& anExclusiveFlag)
{
	myCaptureMouseFlag = anExclusiveFlag;
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
	while(myDIMouse == NULL)
	{
		result = myDirectInput->CreateDevice(GUID_SysMouse, &myDIMouse, NULL);
		if(FAILED(result))
		{
			continue;
		}
		if(myDIMouse == NULL)
		{
			continue;
		}
		result = myDIMouse->Acquire();
		if(FAILED(result))
		{
			continue;
		}
	}
	result = myDIMouse->GetDeviceState(sizeof(myDIMouseState), reinterpret_cast<LPVOID>(&myDIMouseState));
	if(FAILED(result))
	{
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			while(myDIMouse == NULL)
			{
				result = myDirectInput->CreateDevice(GUID_SysMouse, &myDIMouse, NULL);
				if(FAILED(result))
				{
					continue;
				}
				if(myDIMouse == NULL)
				{
					continue;
				}
				result = myDIMouse->Acquire();
				if(FAILED(result))
				{
					continue;
				}
			}
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
	if(myCaptureMouseFlag == true)
	{
		myMousePos.x += myDIMouseState.lX;
		myMousePos.y += myDIMouseState.lY;
	}
	else
	{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(myHWnd,&p);
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


	if(myCaptureMouseFlag == true)
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

InputData InputReader::GetData()
{
	InputData returnData;
	memcpy(&returnData.myKeyboardState,&myDIKeyboardState,sizeof(BYTE)*256);
	returnData.myMouseState = myDIMouseState;
	returnData.myMousePos = myMousePos;
	return returnData;
}