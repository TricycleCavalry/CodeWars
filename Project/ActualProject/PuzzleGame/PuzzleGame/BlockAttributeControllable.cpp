#include "StdAfx.h"
#include "BlockAttributeControllable.h"
#include "MovementDirectionType.h"

#include "Block.h"
#include "Root.h"
#include "OpaqueDictionary.h"

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
}
void BlockAttributeControllable::Update(const float anElapsedTime)
{
	//GrowingArray<Block*> intersectingBlocks = myOwner->GetIntersectingBlocks();
	
	
	if(*myIsMoving == true)
	{		
		Vector2<float> movementDirection;
		GetDirection(myMovementDirectionType,movementDirection);
		myOwner->Move(movementDirection * anElapsedTime * 100);

		
		if( (myOwner->GetPosition()- myEndPosition).Length() < 2.f)
		{
			myOwner->SetPosition(myEndPosition);
			*myIsMoving = false;
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
