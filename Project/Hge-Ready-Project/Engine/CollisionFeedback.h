#ifndef _COLLISION_FEEDBACK_HEADER_
#define _COLLISION_FEEDBACK_HEADER_

enum CollisionOwnerType;

struct CollisionFeedback
{
	CollisionOwnerType myTypeCollidedWith;

	CollisionFeedback()
	{
	}
	CollisionFeedback(const CollisionOwnerType& anOwnerType)
	:	myTypeCollidedWith(anOwnerType)
	{
	}
};

#endif