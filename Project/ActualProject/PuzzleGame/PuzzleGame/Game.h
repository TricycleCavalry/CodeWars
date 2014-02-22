#ifndef _GAME_HEADER_
#define _GAME_HEADER_

#include "Camera.h"

class Level;
class HGE;

class Game
{
public:
	Game(void);
	~Game(void);

	void Init(HGE* aHGE);
	void Update(const float& anElapsedTime);
	void Render();

	
private:
	void LoadLevel();

private:
	HGE* myHGE;
	Level* myLevel;
	Camera myCamera;
	
};

#endif