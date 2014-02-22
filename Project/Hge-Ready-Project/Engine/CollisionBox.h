#ifndef _COLLISION_BOX_HEADER_
#define _COLLISION_BOX_HEADER_

#include "collision.h"

class CollisionBox : public Collision
{
public:
	CollisionBox(CollisionSystem* aCollisionSystem, const Vector2<float>& aPosition, const Vector2<float>& someDimensions, const CollisionOwnerType& anOwnerType);
	~CollisionBox(void);

	bool IsColliding(Collision* aCollision);
	bool IsColliding(CollisionCircle* aCollision);
	bool IsColliding(CollisionBox* aCollision);
	bool IsColliding(CollisionPoint* aCollision);

	Vector2<float> GetDimensions() const;

private:
	Vector2<float> myDimensions;
};

#endif