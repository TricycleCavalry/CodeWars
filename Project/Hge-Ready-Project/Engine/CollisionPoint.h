#ifndef _COLLISION_POINT_HEADER_
#define _COLLISION_POINT_HEADER_

#include "collision.h"
class CollisionPoint : public Collision
{
public:
	CollisionPoint(CollisionSystem* aCollisionSystem, const Vector2<float>& aPosition, const CollisionOwnerType& anOwnerType);
	~CollisionPoint(void);

	bool IsColliding(Collision* aCollision);
	bool IsColliding(CollisionCircle* aCollision);
	bool IsColliding(CollisionBox* aCollision);
	bool IsColliding(CollisionPoint* aCollision);
};

#endif