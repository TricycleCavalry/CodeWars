#include "Root.h"

Root* Root::myInstance(NULL);

Root::Root()
:	myLevel(NULL)
{
}

Root::~Root()
{

}

void Root::Create()
{
	myInstance = new Root();
	
	myInstance->Init();
}

Root* Root::GetInstance()
{
	return myInstance;
}

void Root::Init()
{
	
}

void Root::SetLevel(Level* aLevel)
{
	myLevel = aLevel;
}

Level* Root::GetLevel()
{
	return myLevel;
}