#ifndef _COMPONENT_HEADER_
#define _COMPONENT_HEADER_

#include "ComponentTypes.h"

class Entity;

class Component
{
public:
	Component(const ComponentTypes& aType);
	Component(const ComponentTypes& aType, Entity* anOwner);
	virtual ~Component(void);

	void SetOwner(Entity* anOwner);

	ComponentTypes GetType() const;

	virtual void Update(const float& anElapsedTime)=0;

	virtual void Render();

protected:
	ComponentTypes myType;

	Entity* myOwner;
};

#endif