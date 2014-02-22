#include "StdAfx.h"
#include "BlockManager.h"
#include "Block.h"

BlockManager::BlockManager(void)
:	myBlocks(64)
{
}

BlockManager::~BlockManager(void)
{
}

void BlockManager::Update(const float anElapsedTime)
{
	for(int i = 0; i < myBlocks.Count(); ++i)
	{
		myBlocks[i]->Update(anElapsedTime);
	}
}
void BlockManager::Render(const Vector2<float>& aCameraPosition)
{
	for(int i=0,count=myBlocks.Count();i<count;i++)
	{
		myBlocks[i]->Render(aCameraPosition);
	}
}
void BlockManager::AddBlock(Block* aBlock)
{
	myBlocks.Add(aBlock);
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
void BlockManager::Clear()
{
	myBlocks.RemoveAll();
}