#ifndef _CONTROLL_MANAGER_H_
#define _CONTROLL_MANAGER_H_

#include "GrowingArray.h"
#include "StaticArray.h"

enum MovementDirectionType;
class Block;

enum ControllInputType
{
	CIT_SWITCH_BLOCK_FORWARD,
	CIT_SWITCH_BLOCK_BACKWARD,
	CIT_MOVE_BLOCK_UP,
	CIT_MOVE_BLOCK_DOWN,
	CIT_MOVE_BLOCK_LEFT,
	CIT_MOVE_BLOCK_RIGHT,
	CIT_NUM,
};

class BlockAttributeControllable;

class ControllManager
{
public:
	ControllManager(void);
	~ControllManager(void);

	void Update(const float anElapsedTime);

	void AddControllableBlock(Block* aBlock);

private:
	void UpdateInput();
	void SwitchBlock(const int aDirection);
	void MoveBlock(const MovementDirectionType aDirection);

private:
	GrowingArray<BlockAttributeControllable*> myControllableBlockAttributes;
	GrowingArray<Block*> myControllableBlocks;
	int myNumControllableBlocks;

	int myActiveControllableBlockIndex;

	StaticArray<int,CIT_NUM> myInputKeys;

	
	
};
#endif