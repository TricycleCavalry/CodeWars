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
	HWND hWnd = myHGE.System_GetState(HGE_HWND);
	HINSTANCE hInstance = reinterpret_cast<HINSTANCE>(GetWindowLong(hWnd,GWL_HINSTANCE));
	InputHandler::Create(hInstance,hWnd,myHGE.System_GetState(HGE_SCREENWIDTH),myHGE.System_GetState(HGE_SCREENHEIGHT),false);
	
	srand(static_cast<unsigned int>(time(NULL))); 
	DL_Debug::Create();
	Root::Create();
	Root::GetInstance()->GetManagers().mySpriteManager.SetHGE(&myHGE);
	myTimeManager.InitDefaults();
	ROOT->GetFactories().Load();

	myGame.Init(&myHGE);
	return(true);
};


bool App::Destroy()
{
	DL_Debug::Destroy();
	return(true);
}

bool App::Update()
{
	InputHandler::GetInstance()->Update();
	myTimeManager.Update();

	if(InputKeyState(DIK_ESCAPE,DIKS_CLICKED) == true)
	{
		return false;
	}

	float elapsedTime = static_cast<float>(myTimeManager.GetElapsedTime().GetTime());
	myGame.Update(elapsedTime);

	myGame.Update(elapsedTime);

	Render();
	return(true);
}


bool App::Render()
{	
	myHGE.Gfx_BeginScene();
	myHGE.Gfx_Clear(ARGB(1,1,1,1));
	// DO HGE render stuff
	myGame.Render();
	myHGE.Gfx_EndScene();

	return true;
}