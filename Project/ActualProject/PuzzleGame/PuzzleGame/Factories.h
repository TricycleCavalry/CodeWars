#ifndef FACTORIES_HEADER
#define FACTORIES_HEADER

#include "LevelFactory.h"
#include "BlockFactory.h"
#include "BlockAttributeFactory.h"

class Factories
{
public:
	Factories();
	~Factories();

	void Load();
public:

	LevelFactory myLevelFactory;
	BlockFactory myBlockFactory;
	BlockAttributeFactory myBlockAttributeFactory;
};

#endif