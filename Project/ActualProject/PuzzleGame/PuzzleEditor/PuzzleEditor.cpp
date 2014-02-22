// FirstProject.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "PuzzleEditor.h"
#include "hge.h"
#include "App.h"
#include "InputHandler.h"

#define MAX_LOADSTRING 100
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

HGE *hgeCreate()
{
	HGE *hge = hgeCreate(HGE_VERSION);

	/*hge->System_SetState(HGE_LOGFILE,"HGE_Error.log");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH,1600);
	hge->System_SetState(HGE_SCREENWIDTH,720);
	hge->System_SetState(HGE_SCREENBPP,32);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND,false);
	hge->System_SetState(HGE_TITLE,"Level Editor");*/
	hge->System_SetState(HGE_LOGFILE, "HGE_Error.log");
	hge->System_SetState(HGE_RENDERFUNC,false);
	hge->System_SetState(HGE_TITLE, "Hge-ready project");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, SCREEN_WIDTH);
	hge->System_SetState(HGE_SCREENHEIGHT, SCREEN_HEIGHT);
	hge->System_SetState(HGE_SCREENBPP, 32);
	//hge->System_SetState(HGE_SHOWSPLASH,false);
	hge->System_SetState(HGE_USESOUND,false);
	hge->System_SetState(HGE_ZBUFFER,true);

	if( hge->System_Initiate() )
	{
		hge->System_Start();
	}
	else
	{
		hge->System_Shutdown();
		hge->Release();
		hge = NULL;
		MessageBox(NULL, L"Something went wrong.", L"Error", MB_OK | MB_ICONERROR | MB_APPLMODAL );
	}
	return hge;
}

int WINAPI WinMain(HINSTANCE aHinstance, HINSTANCE, LPSTR, int)
{
	HGE *hge = hgeCreate();

	App application( *hge );
	application.Initialize();
	InputHandler::Create(aHinstance,GetActiveWindow(),SCREEN_WIDTH,SCREEN_HEIGHT,false);

	MSG windowsMessage;
	while(1)
	{
		if( PeekMessage(&windowsMessage,NULL,0,0,PM_REMOVE) )
		{
			if( windowsMessage.message == WM_QUIT )
			{
				break;
			}
			TranslateMessage(&windowsMessage);
			DispatchMessage(&windowsMessage);
		}
		else
		{ 
			if( application.Update() == false )
			{
				break;
			}
		}
	}
	
	hge->System_Shutdown();
	hge->Release();


	return 0;
}

