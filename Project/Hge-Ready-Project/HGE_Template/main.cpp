#include "stdafx.h"
#include "app.h"
#include <time.h>

int WINAPI WinMain(HINSTANCE aHInstance, HINSTANCE aPrevHInstance, LPSTR aCommandLine, int aNumberOfCommands)
{
	srand(static_cast<unsigned int>(time(NULL)));
	
	App application;
	application.Init();
	application.Start();
	return 0;
}
