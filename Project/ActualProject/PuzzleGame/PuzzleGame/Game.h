#ifndef _GAME_HEADER_
#define _GAME_HEADER_

class Level;

class Game
{
public:
	Game(void);
	~Game(void);

	void Init();

	void Update(const float& anElapsedTime);
	void Render();
private:
	void LoadLevel();

	Level* myLevel;
};

#endif