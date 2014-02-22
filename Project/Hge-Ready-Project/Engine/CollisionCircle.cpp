#include "CollisionCircle.h"
#include "CollisionBox.h"
#include "CollisionPoint.h"
#include "Intersections.h"


CollisionCircle::CollisionCircle(CollisionSystem* aCollisionSystem, const Vector2<float>& aPosition, const float& aRadius, const CollisionOwnerType& anOwnerType)
:	Collision(aCollisionSystem,aPosition,anOwnerType)
,	myRadius(aRadius)
{
}

CollisionCircle::~CollisionCircle(void)
{
}

bool CollisionCircle::IsColliding(Collision* aCollision)
{
	return aCollision->IsColliding(this);
}

bool CollisionCircle::IsColliding(CollisionCircle* aCollision)
{
	return Intersections::CircleVsCircleIntersection(myPosition,myRadius,aCollision->GetPosition(),aCollision->GetRadius());
}

bool CollisionCircle::IsColliding(CollisionBox* aCollision)
{
	return Intersections::BoxVsCircleIntersection(aCollision->GetPosition(),aCollision->GetDimensions(),myPosition,myRadius);
}

bool CollisionCircle::IsColliding(CollisionPoint* aCollision)
{
	return Intersections::CircleVsPointIntersection(myPosition,myRadius,aCollision->GetPosition());
}

float CollisionCircle::GetRadius() const
{
	return myRadius;
}