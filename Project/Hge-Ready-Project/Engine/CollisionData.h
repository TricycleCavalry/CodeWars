#ifndef _COLLISION_DATA_HEADER_
#define _COLLISION_DATA_HEADER_

class Collision;
enum CollisionOwnerType;

struct CollisionData
{
	Collision* myCollision;
	CollisionOwnerType myOwnerType;

	CollisionData()
	:	myCollision(NULL)
	{
	}
	CollisionData(Collision* aCollision, const CollisionOwnerType& anOwnerType)
	:	myCollision(aCollision)
	,	myOwnerType(anOwnerType)
	{
	}
};

#endif