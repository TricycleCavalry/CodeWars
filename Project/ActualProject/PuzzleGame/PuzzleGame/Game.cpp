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
	//TODO levelFactory style
	myLevel = ROOT->GetFactories().myLevelFactory.CreateLevel("filepath");
	//myLevel = new Level();
	myLevel->Init(Vector2<int>(100,100));
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