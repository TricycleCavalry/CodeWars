#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <string>
#include "Vector2.h"
#include "Vector4.h"
#include "GrowingArray.h"
#include "StaticArray.h"
#include "BlockAttributeType.h"
#include "SpriteWrapper.h"

class BlockAttribute;

class Block
{
public:
	Block(void);
	~Block(void);

	void Init(const Vector2<float>& aPosition, const Vector2<float>& someExtents);
	void Update(const float anElapsedTime);
	void Render(const Vector2<float>& aCameraPosition);
	
	Vector2<float>& GetPosition();
	void Move(const Vector2<float>& aMovementVector);
	void AddAttribute(BlockAttribute* aAttribute);
	void AddAttributes(GrowingArray<Block*>& someAttributes);

	GrowingArray<BlockAttribute*>& GetAttributes();

	GrowingArray<Block*>& GetIntersectingBlocks();
	void SnapToGrid();
	
	template<typename TYPE>
	TYPE* GetAttribute(const BlockAttributeType aType);
	
	void SetBlockSprite(const std::string& aFilePath, const Vector4f& aColor);

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
	
	SpriteWrapper mySprite;
	Vector4f myBlockColor;
};

template<typename TYPE>
TYPE* Block::GetAttribute(const BlockAttributeType aType)
{
	return reinterpret_cast<TYPE*>(myAttributes[aType]);
}

#endif