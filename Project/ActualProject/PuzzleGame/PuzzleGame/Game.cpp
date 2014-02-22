#include "Game.h"

#include "Level.h"

Game::Game(void)
{
}

Game::~Game(void)
{
}

void Game::Init()
{
	//TODO levelFactory style
	myLevel = new Level();
	myLevel->Init(Vector2<int>(100,100));
}

void Game::Update(const float& anElapsedTime)
{
	myLevel->Update(anElapsedTime);
}

void Game::Render()
{
	myLevel->Render();
}