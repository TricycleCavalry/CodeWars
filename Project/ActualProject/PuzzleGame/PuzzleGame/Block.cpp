#include "StdAfx.h"
#include "Block.h"


#include "BlockAttribute.h"
#include "Root.h"

Block::Block(void)
:	myIntersectingBlocks(4)
,	myAttributes(64)
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
void Block::Render(const Vector2<float>& aCameraPosition)
{
	mySprite.Render(myPosition - aCameraPosition);
}
Vector2<float>& Block::GetPosition()
{
	return myPosition;
}
void Block::Move(const Vector2<float>& aMovementVector)
{
	myPosition += aMovementVector;
}
void Block::AddAttribute(BlockAttribute* aAttribute)
{
	BlockAttributeType type = aAttribute->GetType();
	aAttribute->SetOwner(this);
	myAttributes.Add(aAttribute);
}
void Block::AddAttributes(GrowingArray<Block*>& someAttributes)
{

}
GrowingArray<BlockAttribute*>& Block::GetAttributes()
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
void Block::SetZ(float aZ)
{
	mySprite.SetZ(aZ);
}
void Block::SetBlockSprite(const std::string& aFilePath, const Vector4f& aColor)
{
	mySprite = Root::GetInstance()->GetManagers().mySpriteManager.GetSprite(aFilePath);
	myBlockColor = aColor;
	if(aFilePath == "")
	{
		mySprite.SetColor(ARGB(myBlockColor.a,myBlockColor.r,myBlockColor.g,myBlockColor.b));
	}
	mySprite.SetZ(0.75f);
}
void Block::OnEnter()
{
	for( int i = 0; i < myAttributes.Count(); ++i)
	{
//		myAttributes[i]->OnEnter();
	}
}
void Block::OnExit()
{
	for( int i = 0; i < myAttributes.Count(); ++i)
	{
//		myAttributes[i]->OnExit();
	}
}

void Block::Clear()
{
	//TODO
	for( int i = 0; i < myAttributes.Count(); ++i)
	{
//		myAttributes[i]->Clear();
	}
}


Block* Block::Copy()
{
	Block* returnBlock = CONTAINERS.myBlockContainer.GetNewBlock();
	for(int i = 0; i < myAttributes.Count(); ++i)
	{
		//returnBlock->AddAttribute(myAttributes[i]->Copy());
		//returnBlock->GetAttribute<BlockAttribute*>(static_cast<BlockAttributeType>(i)) ->SetOwner(returnBlock);
	}
	returnBlock->mySprite = mySprite;
	returnBlock->myBlockColor = myBlockColor;
	return returnBlock;
}