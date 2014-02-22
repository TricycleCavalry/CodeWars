#include "Intersections.h"

using namespace Intersections;

bool Intersections::BoxVsBoxIntersection(const Vector2<float>& aFirstBoxPosition, const Vector2<float>& aFirstBoxDimensions, const Vector2<float>& aSecondBoxPosition, const Vector2<float>& aSecondBoxDimensions)
{
	Vector2<float> middlePosition = aFirstBoxPosition+(aFirstBoxDimensions/2);
	Vector2<float> otherMiddlePosition = aSecondBoxPosition+(aSecondBoxDimensions/2);
	
	return (abs(middlePosition.x - otherMiddlePosition.x) * 2 <= (aFirstBoxDimensions.x + aSecondBoxDimensions.x))
		&& (abs(middlePosition.y - otherMiddlePosition.y) *2 <= (aFirstBoxDimensions.y + aSecondBoxDimensions.y));
}

bool Intersections::BoxVsCircleIntersection(const Vector2<float>& aBoxPosition, const Vector2<float>& aBoxDimensions, const Vector2<float>& aCirclePosition, const float& aCircleRadius)
{
	Vector2<float> closestPoint = aCirclePosition;
	if(aCirclePosition.x < aBoxPosition.x)
	{
		closestPoint.x = aBoxPosition.x;
	}
	else if(aCirclePosition.x > aBoxPosition.x+aBoxDimensions.x)
	{
		closestPoint.x = aBoxPosition.x+aBoxDimensions.x;
	}

	if(aCirclePosition.y < aBoxPosition.y)
	{
		closestPoint.y = aBoxPosition.y;
	}
	else if(aCirclePosition.y > aBoxPosition.y+aBoxDimensions.y)
	{
		closestPoint.y = aBoxPosition.y+aBoxDimensions.y;
	}

	return (aCirclePosition-closestPoint).Length2() <= aCircleRadius*aCircleRadius;
}

bool Intersections::BoxVsPointIntersection(const Vector2<float>& aBoxPosition, const Vector2<float>& aBoxDimensions, const Vector2<float>& aPointPosition)
{
	Vector2<float> middlePosition = aBoxPosition+(aBoxDimensions/2);
	return (abs(middlePosition.x - aPointPosition.x) * 2 <= aBoxDimensions.x) && (abs(middlePosition.y - aPointPosition.y) * 2 <= aBoxDimensions.y);
}

bool Intersections::CircleVsCircleIntersection(const Vector2<float>& aFirstCirclePosition, const float& aFirstCircleRadius, const Vector2<float>& aSecondCirclePosition, const float& aSecondCircleRadius)
{
	Vector2<float> differenceVector = aFirstCirclePosition-aSecondCirclePosition;
	float totalRadius = aFirstCircleRadius+aSecondCircleRadius;
	return differenceVector.Length2() <= totalRadius*totalRadius;
}

bool Intersections::CircleVsPointIntersection(const Vector2<float>& aCirclePosition, const float& aCircleRadius, const Vector2<float>& aPointPosition)
{
	Vector2<float> differenceVector = aCirclePosition-aPointPosition;
	return differenceVector.Length2() <= aCircleRadius*aCircleRadius;
}

bool Intersections::PointVsPointIntersection(const Vector2<float>& aFirstPoint, const Vector2<float>& aSecondPoint)
{
	return aFirstPoint == aSecondPoint;
}