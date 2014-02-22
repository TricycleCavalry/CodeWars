#ifndef ROOT_HEADER
#define ROOT_HEADER

#include "Containers.h"
#include "Factories.h"

#define ROOT Root::GetInstance()
#define CONTAINERS Root::GetInstance()->GetContainers()
#define FACTORIES Root::GetInstance()->GetFactories()

class Root
{
public:
	static void Create();
	static Root* GetInstance();

	Containers& GetContainers(){return myContainers;};
	Factories& GetFactories(){return myFactories;};
private:
	Root();
	~Root();
private:
	void Init();
private:
	static Root* myInstance;
	
	Containers myContainers;
	Factories myFactories;
};

#endif