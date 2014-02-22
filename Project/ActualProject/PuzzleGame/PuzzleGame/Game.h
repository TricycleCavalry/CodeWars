#ifndef _GAME_HEADER_
#define _GAME_HEADER_

#include "Camera.h"
#include <string>

class Level;
class HGE;

class Game
{
public:
	Game(void);
	~Game(void);

	void Init(HGE* aHGE);
	bool Update(const float& anElapsedTime);
	void Render();

	
private:
	void LoadFirstLevel();
	bool GetNextLevel();
	void LoadLevel(const std::string &aLevelId);

private:
	HGE* myHGE;
	Level* myLevel;
	std::string myCurrentLevel;
	Camera myCamera;
	
};

#endif