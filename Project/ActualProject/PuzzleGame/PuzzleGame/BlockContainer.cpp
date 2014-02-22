#include "BlockContainer.h"

BlockContainer::BlockContainer()
{
}

BlockContainer::~BlockContainer()
{
}

Block* BlockContainer::GetNewBlock()
{
	return &myBlocks.AddEmptyObject();
}

void BlockContainer::ReturnBlock(Block* aBlock)
{
	myBlocks.RemoveObject(aBlock);
}
void BlockContainer::Clear()
{
	myBlocks.Clear();
}