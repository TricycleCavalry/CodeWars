#include "stdafx.h"
#include "Root.h"
#include "Debug.h"
#include "CommonMacros.h"
#include "GraphicsFactory.h"
#include "CollisionFactory.h"

Root* Root::myInstance(NULL);

void Root::Create(Renderer* aRenderer, TimeManager& aTimeManager)
{
	if(myInstance != NULL)
	{
		DL_ASSERT("Instance of class already created");
	}
	myInstance = new Root();
	myInstance->Init(aRenderer,aTimeManager);
}

Root::Root(void)
{
}

Root::~Root(void)
{
}

void Root::Init(Renderer* aRenderer, TimeManager& aTimeManager)
{
	myGraphicsFactory = new GraphicsFactory();
	myCollisionFactory = new CollisionFactory();
	myGraphicsFactory->Init(aRenderer,&aTimeManager);
}

void Root::Destroy()
{
	if(myInstance != NULL)
	{
		SAFE_DELETE(myInstance);
	}
}

Root* Root::GetInstance()
{
	return myInstance;
}