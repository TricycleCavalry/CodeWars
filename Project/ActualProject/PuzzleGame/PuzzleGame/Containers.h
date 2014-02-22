#ifndef CONTAINERS_HEADER
#define CONTAINERS_HEADER

#include "BlockContainer.h"
#include "BlockAttributeContainer.h"

struct Containers
{
	Containers();
	~Containers();
	BlockContainer myBlockContainer;
	BlockAttributeContainer myBlockAttributeContainer;
};

#endif