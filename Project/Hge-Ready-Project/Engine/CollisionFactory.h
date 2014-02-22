#ifndef _COLLISION_FACTORY_HEADER_
#define _COLLISION_FACTORY_HEADER_

#include "basefactory.h"

class CollisionSystem;
class Collision;
enum CollisionOwnerType;

class CollisionFactory : public BaseFactory
{
public:
	CollisionFactory(void);
	~CollisionFactory(void);

	void Init(CollisionSystem* aCollisionSystem);

	Collision* CreateBoxCollision(const Vector2<float>& aPosition, const Vector2<float>& someDimensions, const CollisionOwnerType& anOwnerType);
	Collision* CreateCircleCollision(const Vector2<float>& aCenterPosition, const float& aRadius, const CollisionOwnerType& anOwnerType);
	Collision* CreatePointCollision(const Vector2<float>& aPosition, const CollisionOwnerType& anOwnerType);

private:
	CollisionSystem* myCollisionSystem;
};

#endif