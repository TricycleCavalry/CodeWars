#include "StdAfx.h"
#include "BlockAttributeControllable.h"
#include "MovementDirectionType.h"

#include "Block.h"
#include "Root.h"
#include "OpaqueDictionary.h"
#include "Tile.h"
#include "Level.h"
#include "CommonMacros.h"

BlockAttributeControllable::BlockAttributeControllable(void)
:	BlockAttribute(BAT_CONTROLLABLE)
{
}

BlockAttributeControllable::~BlockAttributeControllable(void)
{
}

void BlockAttributeControllable::Init()
{
	if(myOwner == NULL)
	{
		DL_ASSERT("ControllManager::AddControllableBlock() has failed Owner is nullptr");
	}
	ROOT->GetManagers().myControllManager.AddControllableBlock(myOwner);
	myIsMoving = &myOwner->myDictionary.SetDefault<bool>(BlockVariables::Moving,false);
	myTimeMoved = 0.f;
}
void BlockAttributeControllable::Update(const float anElapsedTime)
{
	//GrowingArray<Block*> intersectingBlocks = myOwner->GetIntersectingBlocks();
	
	
	if(*myIsMoving == true)
	{
		myTimeMoved = MIN(myTimeMoved+(anElapsedTime*10.f),10.f);
		Vector2<float> movementDirection;
		GetDirection(myMovementDirectionType,movementDirection);
		myOwner->Move(movementDirection * (anElapsedTime * 100) *myTimeMoved);

		
		if( (myOwner->GetPosition()- myEndPosition).Length() < 2.f)
		{
			myOwner->SetPosition(myEndPosition);
			*myIsMoving = false;
		}
	}
	else
	{
		myTimeMoved = 0.f;
	}
	Tile *ownerTile = myOwner->GetCurrentTile();
	if(ownerTile != NULL)
	{
		if(ownerTile->GetTileType() == TT_WIN)
		{
			Root::GetInstance()->GetLevel()->FinishLevel();
		}
	}
}

void BlockAttributeControllable::Move(const MovementDirectionType& aMovementDirection,const Vector2<float>& aEndPosition)
{
	*myIsMoving = true;
	myMovementDirectionType = aMovementDirection;
	myEndPosition = aEndPosition;
}
bool BlockAttributeControllable::IsMoving()
{
	return *myIsMoving;
}
void BlockAttributeControllable::Clear()
{
	ROOT->GetManagers().myControllManager.RemoveControllableBlock(myOwner);
}
BlockAttribute* BlockAttributeControllable::SubCopy()
{
	BlockAttributeControllable* returnAttribute = CONTAINERS.myBlockAttributeContainer.GetNewBlockAttribute<BlockAttributeControllable>();	
	returnAttribute->myType = myType;
	return returnAttribute;
}
