#ifndef _INTERSECTIONS_HEADER_
#define _INTERSECTIONS_HEADER_

template<typename>
class Vector2;
template<typename>
class Vector3;
template<typename>
class Matrix44;
template<typename>
class LineSegment3;

#include "Line.h" //2d line
#include "GrowingArray.h"
//template<typename>
//class Line;			

template<typename,int>
class StaticArray;	


class Quad;

namespace Intersections
{
	//2D
	bool RectVsRect(const Vector2<float>& aFirstBoxPosition, const Vector2<float>& aFirstBoxDimensions, const Vector2<float>& aSecondBoxPosition, const Vector2<float>& aSecondBoxDimensions);
	bool RectVsCircle(const Vector2<float>& aBoxPosition, const Vector2<float>& aBoxDimensions, const Vector2<float>& aCirclePosition, const float& aCircleRadius);
	bool RectVsPoint(const Vector2<float>& aBoxPosition, const Vector2<float>& aBoxDimensions, const Vector2<float>& aPointPosition);

	//bool CircleVsLine( const Vector2f &aSpherePos, const float &aRadius, const Vector2f &aRayPosition, const Vector2f &aRayDirection );	
	bool CircleVsCircle(const Vector2<float>& aFirstCirclePosition, const float& aFirstCircleRadius, const Vector2<float>& aSecondCirclePosition, const float& aSecondCircleRadius);
	bool CircleVsPoint(const Vector2<float>& aCirclePosition, const float& aCircleRadius, const Vector2<float>& aPointPosition);

	bool PointVsPoint(const Vector2<float>& aFirstPoint, const Vector2<float>& aSecondPoint);
	bool PointVsBox(const Vector2<float>& aPoint,const Vector2<float>& aBoxMin,const Vector2<float> aBoxMax);

	bool LineVsLine(const Line<float>& aFirstLine, const Line<float>& aSecondLine,Vector2<float>& anOutIntersectionPoint); 
	bool LineVsRay(const Line<float>& aLine, const Line<float>& aRay,Vector2<float>& anOutIntersectionPoint);
	bool LineVsCircle(const Vector2<float> aFirstPoint, const Vector2<float>& aSecondPoint,const Vector2<float>& aCirclePosition, const float& aCircleRadius);
	bool TriangleVsTriangle(const StaticArray<Line<float>,3>& aFirstTriangle, const StaticArray<Line<float>,3>& aSecondTriangle, GrowingArray<Vector2<float>>& someOutIntersectionPoints);
	bool TriangleVsPolygon(const StaticArray<Line<float>,3>& aTriangle, const GrowingArray<Line<float>>& aPolygon, GrowingArray<Vector2<float>>& someOutIntersectionPoints);
	bool CircleVsPolygon(const Vector2f aCirclePos, const float& aRadius, const GrowingArray<Line<float>>& aPolygon);

	//3D
	bool PointVsAABB(const Vector3<float>& aPoint, const Vector3<float>& anAABBPos, const float& aHalfWidth, const float& aHalfHeight, const float& aHalfDepth);

	bool SphereVsSphere(const Vector3<float>& aFirstSpherePosition, const float& aFirstSphereRadius, const Vector3<float>& aSecondSpherePosition, const float& aSecondSphereRadius, Vector3<float>& anIntersectionPoint);
	bool SphereVsBox(const Matrix44<float>& aSphereOrientation, const float& aSphereRadius, const Matrix44<float>& aBoxOrientation, const float& aHalfWidth, const float& aHalfHeight, const float& aHalfDepth);
	bool SphereVsAABB(const Vector3<float>& aSpherePos, const float& aSphereRadius, const Vector3<float>& anAABBPos, const float& aHalfWidth, const float& aHalfHeight, const float& aHalfDepth);
	bool SphereVsRay( const Vector3<float> &aSpherePos, const float &aRadius, const Vector3<float> &aRayPosition, const Vector3<float> &aRayDirection );
	bool SphereVsPoint( const Vector3<float> &aSpherePos, const float &aRadius, const Vector3<float> &aPoint );
	int SphereVsPlane( const Vector3<float> &aPlanePoint, const Vector3<float> &aPlaneNormal, const Vector3<float> &aSpherePosition, const float aSphereRadius);

	bool SwepthSphereVsSphere(const LineSegment3<float>& aLine, float aRadius, const Matrix44<float>& aSphereOrientation, const float& aSphereRadius);

	bool LineVsSphere(const LineSegment3<float>& aLine,const Matrix44<float>& aSphereOrientation, const float& aSphereRadius, Vector3<float>& aIntersectionPoint);

	bool BoxVsBox(const Matrix44<float>& aFirstBoxOrientation, const float& aFirstHalfWidth, const float& aFirstHalfHeight, const float& aFirstHalfDepth, const Matrix44<float>& aSecondBoxOrientation, const float& aSecondHalfWidth, const float& aSecondHalfHeight, const float& aSecondHalfDepth);
};

#endif