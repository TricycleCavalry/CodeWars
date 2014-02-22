#include <stdafx.h>
#include "app.h"
#include "Windows.h"

#include "Engine.h"
#include "StateStack.h"

#include "GameState.h"

#include "Root.h"
#include "tinyxml2.h"
#include "GraphicsFactory.h"

#define VTUNE_TASK_LOG
#include "VTune.h"


App::App()
:	myEngine(NULL)
{
}

App::~App()
{
}

void App::Init()
{
	myEngine = new Engine();
	myEngine->Init();

	Root::Create(&myEngine->GetRenderer(),myEngine->GetTimeManager());

	tinyxml2::XMLDocument* spriteSheetDoc = new tinyxml2::XMLDocument();
	spriteSheetDoc->LoadFile("Scripting/SpriteSheets.xml");
	Root::GetInstance()->myGraphicsFactory->LoadSpriteSheets(spriteSheetDoc);

	tinyxml2::XMLDocument* graphicsDoc = new tinyxml2::XMLDocument();
	graphicsDoc->LoadFile("Scripting/GlobalGraphics.xml");
	Root::GetInstance()->myGraphicsFactory->LoadGraphics(graphicsDoc);
};

void App::Start()
{
	myEngine->Start();

	MSG* windowMessage = new MSG();

	myStateStack.Push(new GameState(myStateStack,myEngine));
	VTUNE_CREATE_AND_BEGIN_TASK("FirstFrame");
	while(myStateStack.Count() > 0)
	{
		if(PeekMessage(windowMessage, NULL, 0, 0, PM_REMOVE))
		{
			if(windowMessage->message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(windowMessage);
			DispatchMessage(windowMessage);
		}
		else
		{
			VTUNE_END_TASK();
			VTUNE_CREATE_AND_BEGIN_TASK("UserFrame");
			VTUNE_CREATE_AND_BEGIN_TASK("Engine");
			myEngine->Update();
			VTUNE_END_TASK();
			VTUNE_CREATE_AND_BEGIN_TASK("Update");
			myStateStack.Update();
			VTUNE_END_TASK();
			VTUNE_CREATE_AND_BEGIN_TASK("Render");
			myStateStack.Render();
			VTUNE_END_TASK();
		}
	}

	
}