#ifndef _COLLISION_CIRCLE_HEADER_
#define _COLLISION_CIRCLE_HEADER_

#include "collision.h"

class CollisionCircle : public Collision
{
public:
	CollisionCircle(CollisionSystem* aCollisionSystem, const Vector2<float>& aPosition, const float& aRadius, const CollisionOwnerType& anOwnerType);
	~CollisionCircle(void);

	bool IsColliding(Collision* aCollision);
	bool IsColliding(CollisionCircle* aCollision);
	bool IsColliding(CollisionBox* aCollision);
	bool IsColliding(CollisionPoint* aCollision);

	float GetRadius() const;

private:
	float myRadius;
};

#endif