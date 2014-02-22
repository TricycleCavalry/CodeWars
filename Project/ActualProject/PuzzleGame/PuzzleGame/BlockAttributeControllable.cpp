#include "StdAfx.h"
#include "BlockAttributeControllable.h"
#include "MovementDirectionType.h"

#include "Block.h"
#include "Root.h"

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
}
void BlockAttributeControllable::Update(const float anElapsedTime)
{

	GrowingArray<Block*> intersectingBlocks = myOwner->GetIntersectingBlocks();
	for(int i = 0; i < intersectingBlocks.Count(); ++i)
	{
		break;
		//TODO have it like dis?
		//if(intersectingBlocks[i]->GetVariable("Blocked") == true)
		{
			myIsMoving = false;
			myOwner->SnapToGrid();
			break;
		}
		
	}
	if(myIsMoving == true)
	{
		Vector2<float> movementDirection;
		GetDirection(myMovementDirectionType,movementDirection);
		myOwner->Move(movementDirection * anElapsedTime);
	}
}

void BlockAttributeControllable::Move(const MovementDirectionType& aMovementDirection)
{
	myIsMoving = true;
	myMovementDirectionType = aMovementDirection;
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
