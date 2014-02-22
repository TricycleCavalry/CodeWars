#include "StdAfx.h"
#include "BlockManager.h"

BlockManager::BlockManager(void)
:	myBlocks(64)
{
}

BlockManager::~BlockManager(void)
{
}

void BlockManager::Update(const float anElapsedTime)
{
}
void BlockManager::Render(const Vector2<float>& aCameraPosition)
{
}
void BlockManager::SetLevel(Level* aLevel)
{
	myLevel = aLevel;
}
void BlockManager::GetIntersectingBlocks(Block* aBlock,GrowingArray<Block*>& someOutIntersectingBlocks)
{
	//TODO detect intersection blocks and add..
}
void BlockManager::SnapBlockToGrid(Block* aBlock)
{
	//TODO: get closest tile and snap block
}