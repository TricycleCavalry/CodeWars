#include <stdafx.h>
#include "hge.h"
#pragma warning (disable:4005)
#include "app.h"
HTEXTURE			tex;

HGE* HGE_Init()
{
	HGE* hgeInstance=NULL;

	hgeInstance=hgeCreate(HGE_VERSION);

	hgeInstance->System_SetState(HGE_LOGFILE, "HGE_Error.log");
//	hgeInstance->System_SetState(HGE_GFXRESTOREFUNC, GfxRestoreFunc);
	hgeInstance->System_SetState(HGE_TITLE, "Project Random");
	hgeInstance->System_SetState(HGE_WINDOWED, true);
	hgeInstance->System_SetState(HGE_SCREENWIDTH, 800);
	hgeInstance->System_SetState(HGE_SCREENHEIGHT, 600);
	hgeInstance->System_SetState(HGE_SCREENBPP, 32);
	hgeInstance->System_SetState(HGE_SHOWSPLASH, false);
	if(!hgeInstance->System_Initiate())
	{
		hgeInstance->System_Shutdown();
		hgeInstance->Release();
		hgeInstance=NULL;
	}

	return hgeInstance;

};

void HGE_Shutdown(HGE* aHGEInstance)
{
	aHGEInstance->System_Shutdown();
	aHGEInstance->Release();
}




int WINAPI WinMain(HINSTANCE aHInstance, HINSTANCE aPrevHInstance, LPSTR aCommandLine, int aNumberOfCommands)
{
	HGE* hgeEngine=HGE_Init();

	if(hgeEngine==NULL) return(-1);
	
	
	MSG windowsMessage;
	App application(*hgeEngine);

	application.Init();

	bool quitFlag=false;

	while (1) 
	{
		// check for messages
		if ( PeekMessage( &windowsMessage, NULL, 0, 0, PM_REMOVE ) ) 
		{
		  // handle or dispatch messages
			if ( windowsMessage.message == WM_QUIT )
			{
				break;
			}
			TranslateMessage( &windowsMessage );
			DispatchMessage( &windowsMessage );
		} 
		else
		{
			if(application.Update()==false)
			{
				break;
			}

		}

	 }

	application.Destroy();

	HGE_Shutdown(hgeEngine);

	// Clean up and shutdown
	return 0;
}
