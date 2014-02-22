#include "CollisionPoint.h"
#include "CollisionCircle.h"
#include "CollisionBox.h"
#include "Intersections.h"


CollisionPoint::CollisionPoint(CollisionSystem* aCollisionSystem, const Vector2<float>& aPosition, const CollisionOwnerType& anOwnerType)
:	Collision(aCollisionSystem,aPosition,anOwnerType)
{
}


CollisionPoint::~CollisionPoint(void)
{
}

bool CollisionPoint::IsColliding(Collision* aCollision)
{
	return aCollision->IsColliding(this);
}

bool CollisionPoint::IsColliding(CollisionCircle* aCollision)
{
	return Intersections::CircleVsPointIntersection(aCollision->GetPosition(),aCollision->GetRadius(),myPosition);
}

bool CollisionPoint::IsColliding(CollisionBox* aCollision)
{
	return Intersections::BoxVsPointIntersection(aCollision->GetPosition(),aCollision->GetDimensions(),myPosition);
}

bool CollisionPoint::IsColliding(CollisionPoint* aCollision)
{
	return Intersections::PointVsPointIntersection(myPosition,aCollision->GetPosition());
}