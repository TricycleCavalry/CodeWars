#include "StdAfx.h"
#include "Block.h"

#include "BlockAttribute.h"

Block::Block(void)
:	myIntersectingBlocks(4)
{
}

Block::~Block(void)
{
}

void Block::Init(const Vector2<float>& aPosition, const Vector2<float>& someExtents)
{
	myPosition = aPosition;
	myExtents = someExtents;
}

void Block::Update(const float anElapsedTime)
{
	myIntersectingBlocks.RemoveAll();
	//TODO: ROOT->myBlockManager->GetIntersectingBlocks(this,myIntersectingBlocks);
	for( int i = 0; i < BAT_NUM; ++i)
	{
		myAttributes[i]->Update(anElapsedTime);
	}
}
void Block::Move(const Vector2<float>& aMovementVector)
{
	myPosition += aMovementVector;
}
void Block::AddAttribute(BlockAttribute* aAttribute)
{
	BlockAttributeType type = aAttribute->GetType();
	myAttributes[type] = aAttribute;
}
StaticArray<BlockAttribute*,BAT_NUM>& Block::GetAttributes()
{
	return myAttributes;
}
GrowingArray<Block*>& Block::GetIntersectingBlocks()
{
	return myIntersectingBlocks;
}
void Block::SnapToGrid()
{
	//TODO:
	//ROOT->myBlockManager->SnapBlockToGrid(this);
}
void Block::OnEnter()
{
	for( int i = 0; i < BAT_NUM; ++i)
	{
//		myAttributes[i]->OnEnter();
	}
}
void Block::OnExit()
{
	for( int i = 0; i < BAT_NUM; ++i)
	{
//		myAttributes[i]->OnExit();
	}
}

void Block::Clear()
{
	for( int i = 0; i < BAT_NUM; ++i)
	{
//		myAttributes[i]->Clear();
	}
}
