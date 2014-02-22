#include "stdafx.h"
#include "InputHandler.h"

InputHandler::InputHandler(void)
{
	memset(&myKeyboardState,0,sizeof(myKeyboardState));
	memset(&myMouseState,0,sizeof(myMouseState));
	myKeyboardClicks.reset();
	myPreviousKeyBoardClicks.reset();
	myMouseClicks.reset();
	myPreviousMouseClicks.reset();
	myMousePos.x = 1024/2;
	myMousePos.y = 768/2;
}

InputHandler::~InputHandler(void)
{
}

void InputHandler::Update(const InputData &anInputUpdate)
{
	memcpy(myKeyboardState,anInputUpdate.myKeyboardState,sizeof(BYTE)*256);
	myMouseState = anInputUpdate.myMouseState;
	myMousePos = anInputUpdate.myMousePos;
	myPreviousKeyBoardClicks = myKeyboardClicks;
	myKeyboardClicks.reset();
	myPreviousMouseClicks = myMouseClicks;
	myMouseClicks.reset();
}

bool InputHandler::IsKeyPressed(BYTE aKey)
{
	if(myKeyboardState[aKey] & 0x80)
	{
		myKeyboardClicks[aKey] = IS_CLICKED;
		return true;
	}
	return false;
}

bool InputHandler::IsKeyClicked(BYTE aKey)
{
	if(myKeyboardState[aKey] & 0x80)
	{
		myKeyboardClicks[aKey] = IS_CLICKED;
		if(myPreviousKeyBoardClicks[aKey] == IS_CLICKED)
		{
			return false;
		}
		return true;
	}
	return false;
}

int InputHandler::GetClickedKey()
{
	for(int i=0;i<256;i++)
	{
		if(IsKeyClicked(i))
		{
			return (i);
		}
	}
	return -1;
}

bool InputHandler::IsMouseButtonPressed(BYTE aButton)
{
	if(myMouseState.rgbButtons[aButton])
	{
		myMouseClicks[aButton] = IS_CLICKED;
		return true;
	}
	return false;
}

bool InputHandler::IsMouseButtonClicked(BYTE aButton)
{
	if(myMouseState.rgbButtons[aButton])
	{
		myMouseClicks[aButton] = IS_CLICKED;
		if(myPreviousMouseClicks[aButton] == IS_CLICKED)
		{
			return false;
		}
		return true;
	}
	return false;
}

int InputHandler::GetMouseWheelChange()
{
	return myMouseState.lZ;
}

Vector2<float> InputHandler::GetMousePos()
{
	return Vector2<float>(static_cast<float>(myMousePos.x),static_cast<float>(myMousePos.y));
}

void InputHandler::SetKeyState(BYTE aKey, const bool& aBoolFlag)
{
	myKeyboardState[aKey] = aBoolFlag;
}

void InputHandler::SetMouseButtonState(BYTE aButton, const bool& aBoolFlag)
{
	myMouseState.rgbButtons[aButton] = aBoolFlag;
}

void InputHandler::SetMousePos(const Vector2<float>& aNewPos)
{
	myMousePos = Vector2<int>(static_cast<int>(aNewPos.x),static_cast<int>(aNewPos.y));
}