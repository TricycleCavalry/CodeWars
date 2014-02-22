#ifndef _BLOCK_MANAGER_H_
#define _BLOCK_MANAGER_H_

class Block;
class Level;

#include "GrowingArray.h"

class BlockManager
{
public:
	BlockManager(void);
	~BlockManager(void);

	void AddBlock(Block* aBlock);

	void SetLevel(Level* aLevel);
	void GetIntersectingBlocks(Block* aBlock,GrowingArray<Block*>& someOutIntersectingBlocks);

	void SnapBlockToGrid(Block* aBlock);


	//bool Collision(Block* aBlock,GrowingArray<Block*>& someOutColli);

private:
	Level* myLevel;
	GrowingArray<Block*> myBlocks;
};

#endif