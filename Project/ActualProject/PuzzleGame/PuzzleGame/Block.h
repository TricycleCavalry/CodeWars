#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Vector2.h"
#include "GrowingArray.h"
#include "StaticArray.h"
#include "BlockAttributeType.h"

class BlockAttribute;

class Block
{
public:
	Block(void);
	~Block(void);

	void Init(const Vector2<float>& aPosition, const Vector2<float>& someExtents);
	void Update(const float anElapsedTime);
	
	void Move(const Vector2<float>& aMovementVector);
	void AddAttribute(BlockAttribute* aAttribute);
	void AddAttributes(GrowingArray<Block*>& someAttributes);

	GrowingArray<BlockAttribute*>& GetAttributes();

	GrowingArray<Block*>& GetIntersectingBlocks();
	void SnapToGrid();
	
	template<typename TYPE>
	TYPE* GetAttribute(const BlockAttributeType aType);
	

	void OnEnter();
	void OnExit();
	void Clear();

	Block* Copy();

private:


private:
	Vector2<float> myPosition;
	Vector2<float> myExtents;
	GrowingArray<BlockAttribute*> myAttributes;
	GrowingArray<Block*> myIntersectingBlocks;

};

template<typename TYPE>
TYPE* Block::GetAttribute(const BlockAttributeType aType)
{
	return reinterpret_cast<TYPE*>(myAttributes[aType]);
}

#endif