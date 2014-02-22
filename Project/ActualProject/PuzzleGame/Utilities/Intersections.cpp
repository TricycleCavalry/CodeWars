#include "Intersections.h"

#include "Vector2.h"
#include "Vector3.h"
#include "PlaneVolume.h"
#include "Quad.h"
#include "LineSegment3D.h"
#include "Line.h"
#include "StaticArray.h"
#include "TGAMath.h"

using namespace Intersections;

bool Intersections::RectVsRect(const Vector2<float>& aFirstBoxPosition, const Vector2<float>& aFirstBoxDimensions, const Vector2<float>& aSecondBoxPosition, const Vector2<float>& aSecondBoxDimensions)
{
	Vector2<float> middlePosition = aFirstBoxPosition+(aFirstBoxDimensions*0.5f);
	Vector2<float> otherMiddlePosition = aSecondBoxPosition+(aSecondBoxDimensions*0.5f);
	
	return (abs(middlePosition.x - otherMiddlePosition.x) * 2 <= (aFirstBoxDimensions.x + aSecondBoxDimensions.x))
		&& (abs(middlePosition.y - otherMiddlePosition.y) *2 <= (aFirstBoxDimensions.y + aSecondBoxDimensions.y));
}

bool Intersections::RectVsCircle(const Vector2<float>& aBoxPosition, const Vector2<float>& aBoxDimensions, const Vector2<float>& aCirclePosition, const float& aCircleRadius)
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

	//Since it's 1 to -1, you know, directX instead of HGE
	if(aCirclePosition.y > aBoxPosition.y)
	{
		closestPoint.y = aBoxPosition.y;
	}
	else if(aCirclePosition.y < aBoxPosition.y+aBoxDimensions.y)
	{
		closestPoint.y = aBoxPosition.y+aBoxDimensions.y;
	}

	return (aCirclePosition-closestPoint).Length2() <= aCircleRadius*aCircleRadius;
}

bool Intersections::RectVsPoint(const Vector2<float>& aBoxPosition, const Vector2<float>& aBoxDimensions, const Vector2<float>& aPointPosition)
{
	Vector2<float> middlePosition = aBoxPosition+(aBoxDimensions/2);
	return (abs(middlePosition.x - aPointPosition.x) * 2 <= aBoxDimensions.x) && (abs(middlePosition.y - aPointPosition.y) * 2 <= aBoxDimensions.y);
}

bool Intersections::CircleVsCircle(const Vector2<float>& aFirstCirclePosition, const float& aFirstCircleRadius, const Vector2<float>& aSecondCirclePosition, const float& aSecondCircleRadius)
{
	Vector2<float> differenceVector = aFirstCirclePosition-aSecondCirclePosition;
	float totalRadius = aFirstCircleRadius+aSecondCircleRadius;
	return differenceVector.Length2() <= totalRadius*totalRadius;
}
//
//bool Intersections::CircleVsLine( const Vector2f &aSpherePos, const float &aRadius, const Vector2f &aRayPosition, const Vector2f &aRayDirection )
//{
//	float dot = (aSpherePos - aRayPosition).Dot(aRayDirection);
//	Vector2f pointOnLine = (aRayDirection * dot) + aRayPosition;
//	float length = ( pointOnLine - aSpherePos ).Length();
//
//	bool debugResult = length < aRadius;
//	return length < aRadius;
//}

bool Intersections::CircleVsPoint(const Vector2<float>& aCirclePosition, const float& aCircleRadius, const Vector2<float>& aPointPosition)
{
	Vector2<float> differenceVector = aCirclePosition-aPointPosition;
	return differenceVector.Length2() <= aCircleRadius*aCircleRadius;
}

bool Intersections::PointVsPoint(const Vector2<float>& aFirstPoint, const Vector2<float>& aSecondPoint)
{
	return aFirstPoint == aSecondPoint;
}
bool Intersections::PointVsBox(const Vector2<float>& aPoint,const Vector2<float>& aBoxMin,const Vector2<float> aBoxMax)
{
	if(aPoint.x >= aBoxMin.x && aPoint.x <= aBoxMax.x)
	{
		if(aPoint.y >= aBoxMin.y && aPoint.y <= aBoxMax.y)
		{
			return true;
		}
	}
	return false;
}
bool Intersections::LineVsLine(const Line<float>& aFirstLine, const Line<float>& aSecondLine,Vector2<float>& anOutIntersectionPoint)
{
	float A1 = aFirstLine.p2.y - aFirstLine.p1.y;
	float B1 = aFirstLine.p1.x - aFirstLine.p2.x;
	float C1 = (A1 * aFirstLine.p1.x) + ( B1 * aFirstLine.p1.y);

	float A2 = aSecondLine.p2.y - aSecondLine.p1.y;
	float B2 = aSecondLine.p1.x - aSecondLine.p2.x;
	float C2 = (A2 * aSecondLine.p1.x) + ( B2 * aSecondLine.p1.y);

	float delta = A1 * B2 - A2 * B1;
	if(delta == 0)
	{
		return false;
	}

	Vector2<float> intersectionPoint((B2 * C1 - B1 * C2)/delta,(A1*C2 - A2*C1)/delta);
	anOutIntersectionPoint = intersectionPoint;




	if( (aFirstLine.p1-aFirstLine.p2).Length2() < (aFirstLine.p1-intersectionPoint).Length2() || (aFirstLine.p1-aFirstLine.p2).Length2() < (aFirstLine.p2-intersectionPoint).Length2() )
	{
		return false;
	}
	if( (aSecondLine.p1-aSecondLine.p2).Length2() < (aSecondLine.p1-intersectionPoint).Length2() || (aSecondLine.p1-aSecondLine.p2).Length2() < (aSecondLine.p2-intersectionPoint).Length2() )
	{
		return false;
	}

	return true;
}

bool Intersections::LineVsCircle(const Vector2<float> aFirstPoint, const Vector2<float>& aSecondPoint,const Vector2<float>& aCirclePosition, const float& aCircleRadius)
{
	float distance1 = (aCirclePosition- aFirstPoint).Length();
	float distance2 = (aCirclePosition- aSecondPoint).Length();

	if(distance1 < aCircleRadius || distance2 < aCircleRadius)
	{
		return true;
	}

	Vector2<float> toCircleCenter = (aCirclePosition - aFirstPoint);
	Vector2<float> lineDir = (aSecondPoint - aFirstPoint).GetNormalize();

	float dot = toCircleCenter.Dot(lineDir);

	if( dot < 0)
	{
		return false;
	}
	Vector2<float> closestPoint;

	if( dot  <= (aSecondPoint - aFirstPoint).Length())
	{
		closestPoint =  aFirstPoint + lineDir * dot; 
	}
	else
	{
		closestPoint = aSecondPoint;
	}

	if((aCirclePosition - closestPoint).Length2() <= aCircleRadius * aCircleRadius)
	{
		return true;
	}
	return false;
}
bool Intersections::TriangleVsTriangle(const StaticArray<Line<float>,3>& aFirstTriangle, const StaticArray<Line<float>,3>& aSecondTriangle, GrowingArray<Vector2<float>>& someOutIntersectionPoints)
{
	Vector2<float> intersectionPoint;
	bool intersection = false;
	for(int i = 0; i < 3; ++i)
	{
		for(int j = 0; j < 3; ++j)
		{			
			if(Intersections::LineVsLine(aFirstTriangle[i],aSecondTriangle[j],intersectionPoint) == true)
			{
				intersection = true;
				someOutIntersectionPoints.Add(intersectionPoint);
			}
		}
	}

	if(intersection == true)
	{
		return true;
	}

	bool inside = false;
	Vector2<float> c0 = (aFirstTriangle[0].p1 + aFirstTriangle[1].p1 + aFirstTriangle[2].p1)/3;
	Vector2<float> c1 = (aSecondTriangle[0].p1 + aSecondTriangle[1].p1 + aSecondTriangle[2].p1)/3;




	for(int i = 0; i < 3; ++i)
	{
		if(aFirstTriangle[i].Inside(c1) == true)
		{
			inside = true;
			continue;
		}
		inside = false;
		break;
	}
	if(inside == true)
	{
		return true;
	}
	for(int i = 0; i < 3; ++i)
	{
		if(aSecondTriangle[i].Inside(c0) == true)
		{
			inside = true;
			continue;
		}
		inside = false;
		break;
	}
	if(inside == true)
	{
		return true;
	}
	return false;
}

bool Intersections::PointVsAABB(const Vector3<float>& aPoint, const Vector3<float>& anAABBPos, const float& aHalfWidth, const float& aHalfHeight, const float& aHalfDepth)
{
	return aPoint.x > anAABBPos.x - aHalfWidth && aPoint.x < anAABBPos.x + aHalfWidth
		&& aPoint.y > anAABBPos.y - aHalfHeight && aPoint.y < anAABBPos.y + aHalfHeight
		&& aPoint.z > anAABBPos.z - aHalfDepth && aPoint.z < anAABBPos.z + aHalfDepth;
}

bool Intersections::SphereVsSphere(const Vector3<float>& aFirstSpherePosition, const float& aFirstSphereRadius, const Vector3<float>& aSecondSpherePosition, const float& aSecondSphereRadius, Vector3<float>& anIntersectionPoint)
{
	Vector3<float> differenceVector = aFirstSpherePosition-aSecondSpherePosition;
	float totalRadius = aFirstSphereRadius+aSecondSphereRadius;
	if(differenceVector.Length2() <= totalRadius*totalRadius)
	{
		if(aSecondSphereRadius > aFirstSphereRadius)
		{
			anIntersectionPoint = (differenceVector.GetNormalize()*-1.f)*aFirstSphereRadius+aFirstSpherePosition;
		}
		else
		{
			anIntersectionPoint = differenceVector.GetNormalize()*aSecondSphereRadius+aSecondSpherePosition;
		}
		return true;
	}
	return false;
}

bool Intersections::SphereVsAABB(const Vector3<float>& aSpherePos, const float& aSphereRadius, const Vector3<float>& anAABBPos, const float& aHalfWidth, const float& aHalfHeight, const float& aHalfDepth)
{
	Vector3<float> closestPoint = aSpherePos;

	if(closestPoint.x < anAABBPos.x-aHalfWidth)
	{
		closestPoint.x = anAABBPos.x-aHalfWidth;
	}
	else if(closestPoint.x > anAABBPos.x+aHalfWidth)
	{
		closestPoint.x = anAABBPos.x+aHalfWidth;
	}

	if(closestPoint.y < anAABBPos.y-aHalfHeight)
	{
		closestPoint.y = anAABBPos.y-aHalfHeight;
	}
	else if(closestPoint.y > anAABBPos.y+aHalfHeight)
	{
		closestPoint.y = anAABBPos.y+aHalfHeight;
	}

	if(closestPoint.z < anAABBPos.z-aHalfDepth)
	{
		closestPoint.z = anAABBPos.z-aHalfDepth;
	}
	else if(closestPoint.z > anAABBPos.z+aHalfDepth)
	{
		closestPoint.z = anAABBPos.z+aHalfDepth;
	}

	return SphereVsSphere(aSpherePos, aSphereRadius, closestPoint, 0.f,Vector3<float>(0,0,0));
}

bool Intersections::SphereVsRay( const Vector3<float> &aSpherePos, const float &aRadius, const Vector3<float> &aRayPosition, const Vector3<float> &aRayDirection )
{
	float dot = (aSpherePos - aRayPosition).Dot(aRayDirection);
	Vector3f pointOnLine = (aRayDirection * dot) + aRayPosition;
	float length = ( pointOnLine - aSpherePos ).Length();

	bool debugResult = length < aRadius;
	return length < aRadius;
}
int Intersections::SphereVsPlane( const Vector3<float> &aPlanePoint, const Vector3<float> &aPlaneNormal, const Vector3<float> &aSpherePosition, const float aSphereRadius)
{
	float distance = aPlaneNormal.Dot(aPlanePoint - aSpherePosition);
	if(distance >= aSphereRadius)
	{
		return 1;
	}
	else if(distance <= -aSphereRadius)
	{
		return -1;
	}

	return 0;
}

bool Intersections::SphereVsPoint( const Vector3<float> &aSpherePos, const float &aRadius, const Vector3<float> &aPoint )
{
	Vector3<float> differenceVector = aSpherePos-aPoint;
	return differenceVector.Length2() <= aRadius*aRadius;
}

bool PlaneVolumeVsBoxpts(PlaneVolume<float>& aVolume, Vector3<float>* someCorners)
{
	for(int i=0;i<6;i++)
	{
		if(aVolume.Inside(someCorners[i]) == true)
		{
			return true;
		}

	}
	return false;
}
bool Intersections::SwepthSphereVsSphere(const LineSegment3<float>& aLine, float aRadius, const Matrix44<float>& aSphereOrientation, const float& aSphereRadius)
{
	float extendenSphereRadius = aSphereRadius + aRadius;
	return Intersections::LineVsSphere(aLine,aSphereOrientation,extendenSphereRadius,Vector3<float>(0,0,0));	
}