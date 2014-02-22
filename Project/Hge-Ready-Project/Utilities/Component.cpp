#include "Component.h"

#define NULL 0

Component::Component(const ComponentTypes& aType)
:	myOwner(NULL)
,	myType(aType)
{
}

Component::Component(const ComponentTypes& aType, Entity* anOwner)
:	myOwner(anOwner)
,	myType(aType)
{
}

Component::~Component(void)
{
}

void Component::SetOwner(Entity* anOwner)
{
	myOwner = anOwner;
}

ComponentTypes Component::GetType() const
{
	return myType;
}

void Component::Render()
{
}