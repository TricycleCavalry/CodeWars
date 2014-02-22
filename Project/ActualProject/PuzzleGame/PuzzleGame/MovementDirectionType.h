
#ifndef _MOVEMENT_DIRECTION_TYPE_H_
#define _MOVEMENT_DIRECTION_TYPE_H_
#include "Vector2.h"



enum MovementDirectionType
{
	MDT_NULL = -1,
	MDT_UP,
	MDT_DOWN,
	MDT_LEFT,
	MDT_RIGHT,
};


static void GetDirection(const MovementDirectionType aMovementDirectionType, Vector2<float>& aOutDirection )
{
	switch(aMovementDirectionType)
	{
	case MDT_UP:
		aOutDirection = Vector2<float>(0,-1);
		break;
	case MDT_DOWN:
		aOutDirection = Vector2<float>(0,1);
		break;
	case MDT_LEFT:
		aOutDirection = Vector2<float>(-1,0);
		break;
	case MDT_RIGHT:
		aOutDirection = Vector2<float>(1,0);
		break;
	}
}

#endif