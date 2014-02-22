#include "Game.h"

#include "Level.h"
#include "Root.h"
#include "Factories.h"

Game::Game(void)
{
}

Game::~Game(void)
{
}

void Game::Init()
{
	LoadLevel();
}

void Game::Update(const float& anElapsedTime)
{
	ROOT->GetManagers().myControllManager.Update(anElapsedTime);
	myLevel->Update(anElapsedTime);
}

void Game::Render()
{
	myLevel->Render();
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