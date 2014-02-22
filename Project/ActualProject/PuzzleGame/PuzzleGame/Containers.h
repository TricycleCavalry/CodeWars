#ifndef CONTAINERS_HEADER
#define CONTAINERS_HEADER

#include "BlockContainer.h"
#include "BlockAttributeContainer.h"
#include "SpriteManager.h"

struct Containers
{
	Containers();
	~Containers();
	BlockContainer myBlockContainer;
	BlockAttributeContainer myBlockAttributeContainer;
	SpriteManager mySpriteManager;
};

#endif