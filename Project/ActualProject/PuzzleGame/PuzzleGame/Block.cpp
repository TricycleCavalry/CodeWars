#include "StdAfx.h"
#include "Block.h"


#include "BlockAttribute.h"
#include "Root.h"
#include "Level.h"

Block::Block(void)
:	myIntersectingBlocks(4)
,	myAttributes(64)
,	myDictionary(2048)
,	myCurrentTile(NULL)
{
}

Block::~Block(void)
{
}

void Block::Init(const Vector2<float>& aPosition, const Vector2<float>& someExtents)
{
	myPosition = aPosition;
	myExtents = someExtents;
	for(int i = 0; i < myAttributes.Count(); ++i)
	{
		myAttributes[i]->Init();
	}
	ROOT->GetManagers().myBlockManager.AddBlock(this);
}

void Block::Update(const float anElapsedTime)
{
	myIntersectingBlocks.RemoveAll();
	//TODO: ROOT->myBlockManager->GetIntersectingBlocks(this,myIntersectingBlocks);
	for( int i = 0; i < myAttributes.Count(); ++i)
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
void Block::SetPosition(const Vector2<float>& aPosition)
{
	myPosition = aPosition;
}
void Block::Move(const Vector2<float>& aMovementVector)
{
	myPosition += aMovementVector;
	bool* moving;
	if(myDictionary.Lookup<bool>(BlockVariables::Moving,moving) == true)
	{
		if(*moving == true)
		{
			Vector2f tilePos = myCurrentTile->GetPosition();
			Vector2f difference = myPosition - tilePos;
			if(difference.Length() > 16.f)
			{
				Vector2<int> indexedPos(static_cast<int>(tilePos.x/32.f),static_cast<int>(tilePos.y/32.f));
				Vector2<float> differenceF = difference.GetNormalize();
				indexedPos += Vector2<int>(differenceF.x,differenceF.y);
				myCurrentTile->GetBlocks().RemoveCyclic(this);
				OnExit();
				OnEnter(ROOT->GetLevel()->GetTile(indexedPos));
				myCurrentTile->GetBlocks().Add(this);
			}
		}
	}
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
	
		mySprite.SetColor(ARGB(myBlockColor.a,myBlockColor.r,myBlockColor.g,myBlockColor.b));
	
	mySprite.SetZ(0.75f);
}
void Block::OnEnter(Tile* aTile)
{
	myCurrentTile = aTile;
	for( int i = 0; i < myAttributes.Count(); ++i)
	{
//		myAttributes[i]->OnEnter();
	}
}
void Block::OnExit()
{
	myCurrentTile = NULL;
	for( int i = 0; i < myAttributes.Count(); ++i)
	{
//		myAttributes[i]->OnExit();
	}
}

void Block::Clear()
{
	//TODO
	myCurrentTile = NULL;
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
		returnBlock->AddAttribute(myAttributes[i]->Copy());
		//returnBlock->GetAttribute<BlockAttribute*>(static_cast<BlockAttributeType>(i)) ->SetOwner(returnBlock);
	}
	returnBlock->mySprite = mySprite;
	returnBlock->myBlockColor = myBlockColor;
	return returnBlock;
}