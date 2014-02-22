#ifndef _COLLISION_SYSTEM_HEADER_
#define _COLLISION_SYSTEM_HEADER_

#include "GrowingArray.h"
#include "CollisionData.h"

class Collision;

class CollisionSystem
{
public:
	CollisionSystem(void);
	~CollisionSystem(void);

	void AddStaticCollision(const CollisionData& someCollisionData);
	void AddDynamicCollision(const CollisionData& someCollisionData);

	void CheckCollisions();

private:
	GrowingArray<CollisionData> myStaticCollisions;
	GrowingArray<CollisionData> myDynamicCollisions;
};

#endif