#include "app.h"
#include "hge.h"
#pragma warning ( disable : 4005)
#include "TimeManager.h"
#include "DL_Debug.h"
#include "hgeFont.h"
#include "commonMacros.h"
#include "time.h"
#include "hgeSprite.h"
#include "Vector2.h"
#include "ROOT.h"
#include "Containers.h"


App::App(HGE& aHGE)
:	myHGE(aHGE)
{
}

App::~App()
{
}

bool App::Init()
{
	HWND hWnd = GetForegroundWindow();
	HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(GetWindowLong(hWnd,GWL_HINSTANCE));
	myInputThread.StartThread(hInstance,hWnd,myHGE.System_GetState(HGE_SCREENWIDTH),myHGE.System_GetState(HGE_SCREENHEIGHT),true);
	
	srand(static_cast<unsigned int>(time(NULL))); 
	DL_Debug::Create();
	Root::Create();
	Root::GetInstance()->GetManagers().mySpriteManager.SetHGE(&myHGE);
	myTimeManager.InitDefaults();
	//ROOT->GetFactories().Load();

	myGame.Init();
	return(true);
};


bool App::Destroy()
{
	DL_Debug::Destroy();
	return(true);
}

bool App::Update()
{
	myInputThread.Update();
	GrowingArray<InputData>& inputData = myInputThread.GetInputDataArray();
	if(inputData.Count() > 0)
	{
		//myInputHandler.Update(inputData.GetLast());
	}
	myTimeManager.Update();

	//if(myInputHandler.IsKeyClicked(DIK_ESCAPE) == true)
	{
	//	return false;
	}

	float elapsedTime = static_cast<float>(myTimeManager.GetElapsedTime().GetTime());

	Render();
	return(true);
}


bool App::Render()
{	
	myHGE.Gfx_BeginScene();
	myHGE.Gfx_Clear(0);
	// DO HGE render stuff

	myHGE.Gfx_EndScene();

	return true;
}