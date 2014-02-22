#ifndef FACTORIES_HEADER
#define FACTORIES_HEADER

#include "LevelFactory.h"
#include "BlockFactory.h"
#include "BlockAttributeFactory.h"

struct Factories
{
	LevelFactory myLevelFactory;
	BlockFactory myBlockFactory;
	BlockAttributeFactory myBlockAttributeFactory;
};

#endif