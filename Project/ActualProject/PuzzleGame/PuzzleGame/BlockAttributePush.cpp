
#include "BlockAttributePush.h"

BlockAttributePush::BlockAttributePush(void)
:	BlockAttribute(BAT_PUSH)
{
}

BlockAttributePush::~BlockAttributePush(void)
{
}
void BlockAttributePush::SetPushDirection(const Vector2<float>& aDirection)
{
	myPushDirection = aDirection;
}
