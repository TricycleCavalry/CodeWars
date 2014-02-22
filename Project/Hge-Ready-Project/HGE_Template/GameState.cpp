#include "StdAfx.h"
#include "GameState.h"
#include "Root.h"
#include "GraphicsFactory.h"
#include "Engine.h"
#include "Entity.h"
#include "CollisionFactory.h"
#include "CollisionCircle.h"
#include "LuaState.h"
#include "LuaInterpreter.h"

#define VTUNE_TASK_LOG
#include "VTune.h"

GameState::GameState(StateStack& aStateStack, Engine* anEngine)
:	State(aStateStack,anEngine)
,	myInputHandler(&anEngine->GetInputHandler())
{
}

GameState::~GameState(void)
{
}

void GameState::Init()
{
	myLuaInterpreter = new LuaInterpreter(myInputHandler);
}

int GameState::Update()
{
	static bool pause = false;
	if(myInputHandler->IsKeyClicked(DIK_ESCAPE) == true)
	{
		return 999;
	}

	float elapsedTime = myEngine->GetElapsedTime();
	myLuaInterpreter->Update(elapsedTime);

	return 0;
}

void GameState::Render()
{
	myEngine->CleanRenderQueue();
	myLuaInterpreter->Render();
}