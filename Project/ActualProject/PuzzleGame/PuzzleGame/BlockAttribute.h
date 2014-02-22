#ifndef _BLOCK_ATTRIBUTE_H_
#define _BLOCK_ATTRIBUTE_H_

#include "BlockAttributeType.h"


class Block;

class BlockAttribute
{
public:
	BlockAttribute(BlockAttributeType aType);
	~BlockAttribute(void);

	BlockAttributeType GetType();
	void SetOwner(Block* aBlock);

	virtual void Init();
	virtual void Update(const float anElapsedTime);
	/*virtual void OnEnter();
	virtual void OnExit();
	virtual void Clear();*/

	BlockAttribute* Copy();

protected:	
	virtual BlockAttribute* SubCopy() = 0;

protected:
	Block* myOwner;
	BlockAttributeType myType;

};

#endif