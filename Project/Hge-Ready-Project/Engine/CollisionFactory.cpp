#include "CollisionFactory.h"
#include "CollisionCircle.h"
#include "CollisionBox.h"
#include "CollisionPoint.h"


CollisionFactory::CollisionFactory(void)
:	myCollisionSystem(NULL)
{
}


CollisionFactory::~CollisionFactory(void)
{
}

void CollisionFactory::Init(CollisionSystem* aCollisionSystem)
{
	myCollisionSystem = aCollisionSystem;
}

Collision* CollisionFactory::CreateBoxCollision(const Vector2<float>& aPosition, const Vector2<float>& someDimensions, const CollisionOwnerType& anOwnerType)
{
	return new CollisionBox(myCollisionSystem,aPosition,someDimensions,anOwnerType);
}

Collision* CollisionFactory::CreateCircleCollision(const Vector2<float>& aCenterPosition, const float& aRadius, const CollisionOwnerType& anOwnerType)
{
	return new CollisionCircle(myCollisionSystem,aCenterPosition,aRadius,anOwnerType);
}

Collision* CollisionFactory::CreatePointCollision(const Vector2<float>& aPosition, const CollisionOwnerType& anOwnerType)
{
	return new CollisionPoint(myCollisionSystem,aPosition,anOwnerType);
}