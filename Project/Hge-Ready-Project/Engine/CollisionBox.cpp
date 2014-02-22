#include "CollisionBox.h"
#include "CollisionCircle.h"
#include "CollisionPoint.h"
#include "Intersections.h"


CollisionBox::CollisionBox(CollisionSystem* aCollisionSystem, const Vector2<float>& aPosition, const Vector2<float>& someDimensions, const CollisionOwnerType& anOwnerType)
:	Collision(aCollisionSystem,aPosition,anOwnerType)
,	myDimensions(someDimensions)
{
}

CollisionBox::~CollisionBox(void)
{
}

bool CollisionBox::IsColliding(Collision* aCollision)
{
	return aCollision->IsColliding(this);
}

bool CollisionBox::IsColliding(CollisionCircle* aCollision)
{
	return Intersections::BoxVsCircleIntersection(myPosition,myDimensions,aCollision->GetPosition(),aCollision->GetRadius());
}

bool CollisionBox::IsColliding(CollisionBox* aCollision)
{
	return Intersections::BoxVsBoxIntersection(myPosition,myDimensions,aCollision->GetPosition(),aCollision->GetDimensions());
}

bool CollisionBox::IsColliding(CollisionPoint* aCollision)
{
	return Intersections::BoxVsPointIntersection(myPosition,myDimensions,aCollision->GetPosition());
}

Vector2<float> CollisionBox::GetDimensions() const
{
	return myDimensions;
}