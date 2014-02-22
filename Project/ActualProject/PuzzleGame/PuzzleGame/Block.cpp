#include "StdAfx.h"
#include "Block.h"


#include "BlockAttribute.h"
#include "Root.h"

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

	for(int i = 0; i < BAT_NUM; ++i)
	{
		myAttributes[i]->Init();
	}
	
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
	aAttribute->SetOwner(this);
}
void Block::AddAttributes(GrowingArray<Block*>& someAttributes)
{

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


Block* Block::Copy()
{
	Block* returnBlock = CONTAINERS.myBlockContainer.GetNewBlock();
	for(int i = 0; i < BAT_NUM; ++i)
	{
		returnBlock->AddAttribute(myAttributes[i]->Copy());
		//returnBlock->GetAttribute<BlockAttribute*>(static_cast<BlockAttributeType>(i)) ->SetOwner(returnBlock);
	}	
	return returnBlock;
}