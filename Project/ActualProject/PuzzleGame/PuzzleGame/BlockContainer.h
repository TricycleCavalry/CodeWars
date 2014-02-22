#ifndef BLOCK_CONTAINER_HEADER
#define BLOCK_CONTAINER_HEADER

#include "MemoryContainer.h"
#include "Block.h"

class BlockContainer
{
public:
	BlockContainer();
	~BlockContainer();
	
	Block* GetNewBlock();
	void ReturnBlock(Block* aBlock);
	void Clear();
private:
	MemoryContainer<Block,1024> myBlocks;
};

#endif