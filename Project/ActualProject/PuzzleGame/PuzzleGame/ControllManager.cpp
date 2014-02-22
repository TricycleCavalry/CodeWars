#include "StdAfx.h"
#include "ControllManager.h"

#include "BlockAttributeControllable.h"
#include "MovementDirectionType.h"
#include "block.h"
#include "InputHandler.h"
#include "Block.h"

ControllManager::ControllManager(void)
:	myControllableBlockAttributes(4)
,	myControllableBlocks(4)
,	myActiveControllableBlockIndex(0)
{
}

ControllManager::~ControllManager(void)
{
}



void ControllManager::Update(const float anElapsedTime)
{
	//TODO: what?
	UpdateInput();
}
void ControllManager::AddControllableBlock(Block* aBlock)
{
	BlockAttributeControllable* controllAttribute = aBlock->GetAttribute<BlockAttributeControllable>(BAT_CONTROLLABLE);
	if(controllAttribute != NULL)
	{
		myControllableBlockAttributes.Add(controllAttribute);
		myControllableBlocks.Add(aBlock);
		return;
	}
	DL_PRINT("Failed to add controllable lock to ControllManager");
	

}
void ControllManager::RemoveControllableBlock(Block* aBlock)
{
	//TODO remove
}
void ControllManager::SetCamera(Camera* aCamera)
{
	myCamera = aCamera;
}
void ControllManager::UpdateInput()
{
	InputHandler::GetInstance()->GetClickedKey();
	ControllInputType inputKey = CIT_MOVE_BLOCK_RIGHT; // GetKey for frame

	if(InputKeyState(DIK_UPARROW,DIKS_CLICKED))
	{
		MoveBlock(MDT_UP);
	}
	if(InputKeyState(DIK_DOWNARROW,DIKS_CLICKED))
	{
		MoveBlock(MDT_DOWN);
	}
	if(InputKeyState(DIK_LEFTARROW,DIKS_CLICKED))
	{
		MoveBlock(MDT_LEFT);
	}
	if(InputKeyState(DIK_RIGHTARROW,DIKS_CLICKED))
	{
		MoveBlock(MDT_RIGHT);
	}
	if(InputKeyState(DIK_C,DIKS_CLICKED))
	{
		SwitchBlock(1);
	}
	if(InputKeyState(DIK_V,DIKS_CLICKED))
	{
		SwitchBlock(-1);
	}

	//switch(inputKey)
	//{
	//case CIT_SWITCH_BLOCK_FORWARD:
	//	SwitchBlock(1);
	//	break;
	//case CIT_SWITCH_BLOCK_BACKWARD:
	//	SwitchBlock(-1);
	//	break;
	//case CIT_MOVE_BLOCK_UP:
	//case CIT_MOVE_BLOCK_DOWN:
	//case CIT_MOVE_BLOCK_LEFT:
	//case CIT_MOVE_BLOCK_RIGHT:
	//	MovementDirectionType type = static_cast<MovementDirectionType>(inputKey - CIT_MOVE_BLOCK_UP);
	//	MoveBlock(type);	// MDT_UP == 0,  CIT_MOVE_BLOCK_UP == 2
	//	break;
	//}
}
void ControllManager::SwitchBlock(const int aDirection)
{
	myActiveControllableBlockIndex += aDirection;

	if(myActiveControllableBlockIndex < 0)
	{
		myActiveControllableBlockIndex = myNumControllableBlocks - 1;
	}
	else if(myActiveControllableBlockIndex > myNumControllableBlocks - 1 )
	{
		myActiveControllableBlockIndex = 0;
	}
	myCamera->MoveToPosition(myControllableBlocks[myActiveControllableBlockIndex]->GetPosition(),0.8f);
}
void ControllManager::MoveBlock(const MovementDirectionType aDirection)
{
	myControllableBlockAttributes[myActiveControllableBlockIndex]->Move(aDirection);
}

