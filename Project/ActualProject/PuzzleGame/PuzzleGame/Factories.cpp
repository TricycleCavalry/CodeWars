

#include "Factories.h"

Factories::Factories()
{
}
Factories::~Factories()
{
}
void Factories::Load()
{
	myBlockFactory.LoadTypes("Data\\XML\\BlockTypes.xml");
}