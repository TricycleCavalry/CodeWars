#pragma once
#include "blockattribute.h"
#include "Vector2.h"

class BlockAttributePush :	public BlockAttribute
{
public:
	BlockAttributePush(void);
	~BlockAttributePush(void);

	void SetPushDirection(const Vector2<float>& aDirection);


private:
	Vector2<float> myPushDirection;
};
