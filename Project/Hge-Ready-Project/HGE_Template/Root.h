#ifndef _ROOT_HEADER_
#define _ROOT_HEADER_

class GraphicsFactory;
class CollisionFactory;
class EnemyFactory;
class Renderer;
class TimeManager;

class Root
{
public:
	static void Create(Renderer* aRenderer, TimeManager& aTimeManager);
	static void Destroy();

	void Init(Renderer* aRenderer, TimeManager& aTimeManager);

	static Root* GetInstance();
	
private:
	Root(void);
	~Root(void);

	static Root* myInstance;

public:
	GraphicsFactory* myGraphicsFactory;
	CollisionFactory* myCollisionFactory;
	EnemyFactory* myEnemyFactory;
};

#endif