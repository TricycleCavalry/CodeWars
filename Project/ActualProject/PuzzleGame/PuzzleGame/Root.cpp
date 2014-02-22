#include "Root.h"

Root* Root::myInstance(NULL);

Root::Root()
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