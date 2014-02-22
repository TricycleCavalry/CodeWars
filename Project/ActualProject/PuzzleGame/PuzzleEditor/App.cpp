#include "stdafx.h"
#include "App.h"
#include "hge.h"
#include "InputHandler.h"

App::App( HGE &aHGE )
:	myHGE( aHGE )
{
}

App::~App(void)
{
	myEditor.SaveFile( "Level1.txt" );
}

void App::Initialize()
{
	myEditor.Init(&myHGE);
}

bool App::Update()
{
	InputHandler::GetInstance()->Update();
	myEditor.Update();

	Render();
	return true;
}

void App::Render()
{
	myHGE.Gfx_Clear(0);
	myHGE.Gfx_BeginScene();
	myEditor.Render();
	myHGE.Gfx_EndScene();
}