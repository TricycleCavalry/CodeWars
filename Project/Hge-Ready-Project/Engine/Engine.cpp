#include "Engine.h"

#include "HGE.h"
#include "Renderer.h"
#include "CommonMacros.h"
#include "LuaState.h"

#define VTUNE_TASK_LOG
#include "Vtune.h"

DWORD WINAPI ThreadRenderFunc(void* threadRenderData)
{
	ThreadRenderData* renderData = reinterpret_cast<ThreadRenderData*>(threadRenderData);
	int arrayToRender;
	while(true)
	{	
		if(renderData->myIsAllowedToStartFlag == true)
		{
			renderData->myIsAllowedToStartFlag = false;

			arrayToRender = renderData->myCurrentArrayToRender;

			renderData->myRenderer->Render();
			
			renderData->myIsDoneFlag = true;
			
		}
		else
		{
			Sleep(0);
		}
	}

	return 0;
}

Engine::Engine(void)
:	myHGE(NULL)
,	myRenderer(NULL)
,	myInputHandler(NULL)
{
	Debug::Create();
	LuaState::Create();
}

Engine::~Engine(void)
{
	ShutDownHGE();
	Debug::Destroy();
	SAFE_DELETE(myInputHandler);
}

void Engine::Init()
{
	myHGE = InitiateHGE();

	myInputHandler = new InputHandler();

	myRenderer = new Renderer(myHGE);
	myRenderer->Init();

	myTimeManager.InitDefaults();
}

void Engine::Start()
{
	myHwnd = myHGE->System_GetState(HGE_HWND);
	HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(GetWindowLong(myHwnd, GWL_HINSTANCE));

	StartRenderThread();

	myInputThread.StartThread(hInstance,myHwnd,myHGE->System_GetState(HGE_SCREENWIDTH),myHGE->System_GetState(HGE_SCREENHEIGHT), true);
}

void Engine::Update()
{
	VTUNE_CREATE_AND_BEGIN_TASK("CheckFocus");
	CheckFocus();
	VTUNE_END_TASK();
	myTimeManager.Update();
	VTUNE_CREATE_AND_BEGIN_TASK("InputThread");
	myInputThread.Update();
	VTUNE_END_TASK();

	UpdateInput(myInputThread.GetInputDataArray());

	VTUNE_CREATE_AND_BEGIN_TASK("WaitForRenderer");
	for(;;)
	{
		if(myThreadRenderData.myIsDoneFlag == true)
		{
			myThreadRenderData.myIsAllowedToStartFlag = false;

			myRenderer->SwitchQueues();

			myThreadRenderData.myIsDoneFlag = false;						
			myThreadRenderData.myIsAllowedToStartFlag = true;
			break;
		}
	}
	VTUNE_END_TASK();
}

Renderer& Engine::GetRenderer()
{
	return *myRenderer;
}

InputHandler& Engine::GetInputHandler()
{
	return *myInputHandler;
}

TimeManager& Engine::GetTimeManager()
{
	return myTimeManager;
}

float Engine::GetElapsedTime()
{
	return static_cast<float>(myTimeManager.GetElapsedTime().GetTime());
}

HGE& Engine::GetHGE()
{
	return *myHGE;
}

void Engine::CleanRenderQueue()
{
	myRenderer->CleanQueue();
}

void Engine::StartRenderThread()
{
	HANDLE renderThread;

	int currentArrayToRender = 1;	

	myThreadRenderData.myCurrentArrayToRender = 0;
	myThreadRenderData.myIsAllowedToStartFlag = false;
	myThreadRenderData.myIsDoneFlag = true;
	myThreadRenderData.myRenderer = myRenderer;
	
	renderThread = CreateThread(NULL,2000,&ThreadRenderFunc,reinterpret_cast<void*>(&myThreadRenderData),0,NULL);
}

HGE* Engine::InitiateHGE()
{
	HGE* hgeInstance=NULL;
	int width = 1280;//GetSystemMetrics(SM_CXSCREEN);
	int height = 1024;//GetSystemMetrics(SM_CYSCREEN );

	hgeInstance=hgeCreate(HGE_VERSION);

	hgeInstance->System_SetState(HGE_LOGFILE, "HGE_Error.log");
	hgeInstance->System_SetState(HGE_RENDERFUNC,false);
	hgeInstance->System_SetState(HGE_TITLE, "Hge-ready project");
	hgeInstance->System_SetState(HGE_WINDOWED, true);
	hgeInstance->System_SetState(HGE_SCREENWIDTH, width);
	hgeInstance->System_SetState(HGE_SCREENHEIGHT, height);
	hgeInstance->System_SetState(HGE_SCREENBPP, 32);
	hgeInstance->System_SetState(HGE_SHOWSPLASH,false);
	hgeInstance->System_SetState(HGE_USESOUND,false);
	hgeInstance->System_SetState(HGE_ZBUFFER,true);

	if(!hgeInstance->System_Initiate())
	{
		hgeInstance->System_Shutdown();
		hgeInstance->Release();
		hgeInstance=NULL;
	}
	return hgeInstance;
};

void Engine::ShutDownHGE()
{
	myHGE->System_Shutdown();
	myHGE->Release();
}

void Engine::UpdateInput(GrowingArray<InputData>& someInputData)
{
	if(someInputData.Count() > 0)
	{
		InputData& inputStuff = someInputData.GetLast();
		if(inputStuff.myKeyboardState[0] != 0)
		{
			int i = 3;
		}
		myInputHandler->Update(inputStuff);
	}
	someInputData.RemoveAll();
}


void Engine::CheckFocus()
{
	if(GetFocus() != myHwnd)
	{
		MSG windowMessage;
		while(true)
		{
			PeekMessage(&windowMessage,myHwnd,0,0,PM_REMOVE);
			TranslateMessage(&windowMessage);
			DispatchMessage(&windowMessage);

			if(GetFocus() == myHwnd)
			{
				myInputThread.ReCaptureMouse(myHwnd);
				LuaState::GetInstance()->ReloadScripts();
				myTimeManager.Update();
				return;
			}
		}
	}
}