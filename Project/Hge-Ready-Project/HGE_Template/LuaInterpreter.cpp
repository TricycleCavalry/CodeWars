#include "stdafx.h"
#include "LuaInterpreter.h"
#include "LuaState.h"
#include "InputHandler.h"
#include "Root.h"
#include "GraphicsFactory.h"
#include "Font.h"

LuaInterpreter::LuaInterpreter(InputHandler* anInputHandler)
:	myLuaState(LuaState::GetInstance())
,	myIsSwitchedOn(false)
,	myEnteredString("")
,	myFont(Root::GetInstance()->myGraphicsFactory->GetFont("UI12"))
,	myInputHandler(anInputHandler)
,	myTextPositionIndicatorTimer(0.f)
,	myOldStrings(8)
{
}


LuaInterpreter::~LuaInterpreter(void)
{
}

void LuaInterpreter::Update(const float& anElapsedTime)
{
	myTextPositionIndicatorTimer += anElapsedTime;
	if(myTextPositionIndicatorTimer > 1.f)
	{
		myTextPositionIndicatorTimer = 0.f;
	}
	HandleInput();
}

void LuaInterpreter::Render()
{
	if(myIsSwitchedOn == true)
	{
		std::string stringToRender = myEnteredString;
		if(myTextPositionIndicatorTimer < 0.5f)
		{
			stringToRender += '_';
		}
		myFont->Render(Vector2<float>(0.f,0.f),0.f,0,1.f,HGETEXT_LEFT,stringToRender);
	}
}

bool LuaInterpreter::IsOn() const
{
	return myIsSwitchedOn;
}

void LuaInterpreter::HandleInput()
{
	static int oldStringCounter = -1;
	if(myInputHandler->IsKeyClicked(DIK_GRAVE) == true)
	{
		myIsSwitchedOn = !myIsSwitchedOn;
	}

	if(myIsSwitchedOn == true)
	{
		BYTE pressedKey = myInputHandler->GetClickedKey();
		if(pressedKey == 0 || pressedKey == DIK_GRAVE || pressedKey == DIK_LSHIFT)
		{
			return;
		}

		if(pressedKey == DIK_BACK)
		{
			if(myEnteredString.length() > 0)
			{
				if(myInputHandler->IsKeyPressed(DIK_LSHIFT) == true)
				{
					myEnteredString.clear();
				}
				else
				{
					myEnteredString.pop_back();
				}
			}
			return;
		}

		if(pressedKey == DIK_UP)
		{
			if(oldStringCounter+1 < myOldStrings.Count())
			{
				oldStringCounter++;
				myEnteredString = myOldStrings[oldStringCounter];
			}
			return;
		}

		if(pressedKey == DIK_DOWN)
		{
			if(oldStringCounter > 0)
			{
				oldStringCounter--;
				myEnteredString = myOldStrings[oldStringCounter];
			}
			return;
		}

		if(pressedKey == DIK_RETURN)
		{
			myLuaState->RunString(myEnteredString,true);
			myOldStrings.Insert(0,myEnteredString);
			myEnteredString.clear();
			oldStringCounter = -1;
			return;
		}

		int asciiKey = myInputHandler->Scan2Ascii(pressedKey,myInputHandler->IsKeyPressed(DIK_LSHIFT));

		if(asciiKey != -1)
		{
			myEnteredString += static_cast<char>(asciiKey);
		}
	}
}