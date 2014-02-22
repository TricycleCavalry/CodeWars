#include "Game.h"

#include "Level.h"
#include "Root.h"
#include "Factories.h"

#include "InputHandler.h"
#include "Camera.h"

Game::Game(void)
:	myHGE(NULL)
{
}

Game::~Game(void)
{
}

void Game::Init(HGE* aHGE)
{
	ROOT->GetManagers().myControllManager.SetCamera(&myCamera);
	myHGE = aHGE;
	LoadLevel();

}

void Game::Update(const float& anElapsedTime)
{
	Vector2<float> camPos = myCamera.GetPosition();
	if(InputKeyState(DIK_UPARROW,DIKS_PRESSED) == true)
	{
		camPos.myY -= 500 * anElapsedTime;
		
	}
	if(InputKeyState(DIK_DOWN,DIKS_PRESSED) == true)
	{
		camPos.myY += 500 * anElapsedTime;
		
	}
	if(InputKeyState(DIK_RIGHTARROW,DIKS_PRESSED) == true)
	{
		camPos.myX += 500 * anElapsedTime;
		
	}
	if(InputKeyState(DIK_LEFTARROW,DIKS_PRESSED) == true)
	{
		camPos.myX -= 500 * anElapsedTime;
		
	}
	myCamera.SetPosition(camPos);
	myCamera.Update(anElapsedTime);
	ROOT->GetManagers().myControllManager.Update(anElapsedTime);
	myLevel->Update(anElapsedTime);
}

void Game::Render()
{
	myLevel->Render(myCamera.GetPosition());
}

void Game::LoadLevel()
{
	tinyxml2::XMLElement* levelElement = XMLUTIL::LoadFile("Data/XML/Levels.xml");
	std::string startLevelId = levelElement->Attribute("StartLevelId");
	levelElement = levelElement->FirstChildElement("Level");

	std::string filePath = "None";
	while(levelElement != NULL)
	{
		if(XMLUTIL::GetString(levelElement,"ID") == startLevelId)
		{
			filePath = XMLUTIL::GetString(levelElement,"FilePath");
			break;
		}
		levelElement = levelElement->NextSiblingElement();
	}

	if(filePath == "None")
	{
		DL_ASSERT("No level with the Id: %s was found",startLevelId.c_str());
	}

	myLevel = FACTORIES.myLevelFactory.CreateLevel(filePath);
	
}