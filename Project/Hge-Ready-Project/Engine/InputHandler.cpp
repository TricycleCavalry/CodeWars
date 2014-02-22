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
	myKeyboardLayout = GetKeyboardLayout(0);
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
		if(IsKeyClicked(i) == true)
		{
			return i;
		}
	}
	return 0;
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

int InputHandler::Scan2Ascii(DWORD aScanCode, bool aShiftFlag)
{
	switch(aScanCode)
	{
	case DIK_1:
		if(aShiftFlag == true)
		{
			return '!';
		}
		else
		{
			return '1';
		}
	case DIK_2:
		if(aShiftFlag == true)
		{
			return '@';
		}
		else
		{
			return '2';
		}
	case DIK_3:
		if(aShiftFlag == true)
		{
			return '#';
		}
		else
		{
			return '3';
		}
	case DIK_4:
		if(aShiftFlag == true)
		{
			return '$';
		}
		else
		{
			return '4';
		}
	case DIK_5:
		if(aShiftFlag == true)
		{
			return '%';
		}
		else
		{
			return '5';
		}
	case DIK_6:
		if(aShiftFlag == true)
		{
			return '^';
		}
		else
		{
			return '6';
		}
	case DIK_7:
		if(aShiftFlag == true)
		{
			return '&';
		}
		else
		{
			return '7';
		}
	case DIK_8:
		if(aShiftFlag == true)
		{
			return '*';
		}
		else
		{
			return '8';
		}
	case DIK_9:
		if(aShiftFlag == true)
		{
			return '(';
		}
		else
		{
			return '9';
		}
	case DIK_0:
		if(aShiftFlag == true)
		{
			return ')';
		}
		else
		{
			return '0';
		}
	case DIK_MINUS:
		if(aShiftFlag == true)
		{
			return '_';
		}
		else
		{
			return '-';
		}
	case DIK_EQUALS:
		if(aShiftFlag == true)
		{
			return '+';
		}
		else
		{
			return '=';
		}
	case DIK_Q:
		if(aShiftFlag == true)
		{
			return 'Q';
		}
		else
		{
			return 'q';
		}
	case DIK_W:
		if(aShiftFlag == true)
		{
			return 'W';
		}
		else
		{
			return 'w';
		}
	case DIK_E:
		if(aShiftFlag == true)
		{
			return 'E';
		}
		else
		{
			return 'e';
		}
	case DIK_R:
		if(aShiftFlag == true)
		{
			return 'R';
		}
		else
		{
			return 'r';
		}
	case DIK_T:
		if(aShiftFlag == true)
		{
			return 'T';
		}
		else
		{
			return 't';
		}
	case DIK_Y:
		if(aShiftFlag == true)
		{
			return 'Y';
		}
		else
		{
			return 'y';
		}
	case DIK_U:
		if(aShiftFlag == true)
		{
			return 'U';
		}
		else
		{
			return 'u';
		}
	case DIK_I:
		if(aShiftFlag == true)
		{
			return 'I';
		}
		else
		{
			return 'i';
		}
	case DIK_O:
		if(aShiftFlag == true)
		{
			return 'O';
		}
		else
		{
			return 'o';
		}
	case DIK_P:
		if(aShiftFlag == true)
		{
			return 'P';
		}
		else
		{
			return 'p';
		}
	case DIK_LBRACKET:
		if(aShiftFlag == true)
		{
			return '{';
		}
		else
		{
			return '[';
		}
	case DIK_RBRACKET:
		if(aShiftFlag == true)
		{
			return '}';
		}
		else
		{
			return ']';
		}
	case DIK_A:
		if(aShiftFlag == true)
		{
			return 'A';
		}
		else
		{
			return 'a';
		}
	case DIK_S:
		if(aShiftFlag == true)
		{
			return 'S';
		}
		else
		{
			return 's';
		}
	case DIK_D:
		if(aShiftFlag == true)
		{
			return 'D';
		}
		else
		{
			return 'd';
		}
	case DIK_F:
		if(aShiftFlag == true)
		{
			return 'F';
		}
		else
		{
			return 'f';
		}
	case DIK_G:
		if(aShiftFlag == true)
		{
			return 'G';
		}
		else
		{
			return 'g';
		}
	case DIK_H:
		if(aShiftFlag == true)
		{
			return 'H';
		}
		else
		{
			return 'h';
		}
	case DIK_J:
		if(aShiftFlag == true)
		{
			return 'J';
		}
		else
		{
			return 'j';
		}
	case DIK_K:
		if(aShiftFlag == true)
		{
			return 'K';
		}
		else
		{
			return 'k';
		}
	case DIK_L:
		if(aShiftFlag == true)
		{
			return 'L';
		}
		else
		{
			return 'l';
		}
	case DIK_SEMICOLON:
		if(aShiftFlag == true)
		{
			return ':';
		}
		else
		{
			return ';';
		}
	case DIK_APOSTROPHE:
		if(aShiftFlag == true)
		{
			return static_cast<char>(39);
		}
		else
		{
			return static_cast<char>(34);
		}
	case DIK_GRAVE:
		if(aShiftFlag == true)
		{
			return '~';
		}
		else
		{
			return '`';
		}
	case DIK_BACKSLASH:
		if(aShiftFlag == true)
		{
			return static_cast<char>(92);
		}
		else
		{
			return '|';
		}
	case DIK_Z:
		if(aShiftFlag == true)
		{
			return 'Z';
		}
		else
		{
			return 'z';
		}
	case DIK_X:
		if(aShiftFlag == true)
		{
			return 'X';
		}
		else
		{
			return 'x';
		}
	case DIK_C:
		if(aShiftFlag == true)
		{
			return 'C';
		}
		else
		{
			return 'c';
		}
	case DIK_V:
		if(aShiftFlag == true)
		{
			return 'V';
		}
		else
		{
			return 'v';
		}
	case DIK_B:
		if(aShiftFlag == true)
		{
			return 'B';
		}
		else
		{
			return 'b';
		}
	case DIK_N:
		if(aShiftFlag == true)
		{
			return 'N';
		}
		else
		{
			return 'n';
		}
	case DIK_M:
		if(aShiftFlag == true)
		{
			return 'M';
		}
		else
		{
			return 'm';
		}
	case DIK_COMMA:
		if(aShiftFlag == true)
		{
			return '<';
		}
		else
		{
			return ',';
		}
	case DIK_PERIOD:
		if(aShiftFlag == true)
		{
			return '>';
		}
		else
		{
			return '.';
		}
	case DIK_SLASH:
		if(aShiftFlag == true)
		{
			return '?';
		}
		else
		{
			return '/';
		}
	case DIK_SPACE:
		return ' ';
	}
	return -1;
}

bool InputHandler::CheckValidSymbol(BYTE aKey)
{
	if( (aKey > 1 && aKey < 14)
		|| (aKey > 15 && aKey < 28)
		|| (aKey > 29 && aKey < 54 && aKey != 42)
		|| (aKey == 55) || (aKey == 57))
	{
		return true;
	}
	return false;
}