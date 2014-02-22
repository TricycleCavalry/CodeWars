#include "Game.h"

#include "Level.h"
#include "Root.h"
#include "Factories.h"

#include "InputHandler.h"
#include "Camera.h"

Game::Game(void)
:	myHGE(NULL)
,	myLevel(NULL)
{
}

Game::~Game(void)
{
}

void Game::Init(HGE* aHGE)
{
	ROOT->GetManagers().myControllManager.SetCamera(&myCamera);
	myHGE = aHGE;
	LoadFirstLevel();
}

bool Game::Update(const float& anElapsedTime)
{
	myCamera.Update(anElapsedTime);
	ROOT->GetManagers().myBlockManager.Update(anElapsedTime);
	ROOT->GetManagers().myControllManager.Update(anElapsedTime);
	if(myLevel->Update(anElapsedTime) == false)
	{
		Root::GetInstance()->GetContainers().myBlockContainer.Clear();
		Root::GetInstance()->GetContainers().myBlockAttributeContainer.ClearAttribute();
		Root::GetInstance()->GetManagers().myBlockManager.Clear();
		Root::GetInstance()->GetManagers().myControllManager.Clear();
		
		delete myLevel;
		myLevel = NULL;
		if(GetNextLevel() == false)
		{
			return false;
		}
	}
	return true;
}

void Game::Render()
{
	Vector2f cameraPos = myCamera.GetPosition();
	myLevel->Render(cameraPos);
	ROOT->GetManagers().myBlockManager.Render(cameraPos);
}
void Game::LoadFirstLevel()
{
	tinyxml2::XMLElement* levelElement = XMLUTIL::LoadFile("Data/XML/Levels.xml");
	std::string levelId = levelElement->Attribute("StartLevelId");
	LoadLevel(levelId);
}
bool Game::GetNextLevel()
{
	tinyxml2::XMLElement* levelElement = XMLUTIL::LoadFile("Data/XML/Levels.xml");
	levelElement = levelElement->FirstChildElement("Level");

	std::string nextLevel = "None";
	while(levelElement != NULL)
	{
		if(XMLUTIL::GetString(levelElement,"ID") == myCurrentLevel)
		{
			levelElement = levelElement->NextSiblingElement();
			if(levelElement != NULL)
			{
				nextLevel = XMLUTIL::GetString(levelElement,"ID");
			}
			break;
		}
		levelElement = levelElement->NextSiblingElement();
	}
	if(nextLevel != "None")
	{
		LoadLevel(nextLevel);
		return true;
	}
	else
	{
		return false;
	}
}
void Game::LoadLevel(const std::string &aLevelId)
{
	tinyxml2::XMLElement* levelElement = XMLUTIL::LoadFile("Data/XML/Levels.xml");
	levelElement = levelElement->FirstChildElement("Level");

	std::string filePath = "None";
	while(levelElement != NULL)
	{
		if(XMLUTIL::GetString(levelElement,"ID") == aLevelId)
		{
			filePath = XMLUTIL::GetString(levelElement,"FilePath");
			break;
		}
		levelElement = levelElement->NextSiblingElement();
	}

	if(filePath == "None")
	{
		DL_ASSERT("No level with the Id: %s was found",aLevelId.c_str());
	}

	myCurrentLevel = aLevelId;
	myLevel = FACTORIES.myLevelFactory.CreateLevel(filePath);
	ROOT->GetManagers().myControllManager.SetLvel(myLevel);
	ROOT->SetLevel(myLevel);
}