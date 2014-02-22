#ifndef _INTERSECTIONS_HEADER_
#define _INTERSECTIONS_HEADER_

#include "Vector2.h"

namespace Intersections
{
	bool BoxVsBoxIntersection(const Vector2<float>& aFirstBoxPosition, const Vector2<float>& aFirstBoxDimensions, const Vector2<float>& aSecondBoxPosition, const Vector2<float>& aSecondBoxDimensions);
	bool BoxVsCircleIntersection(const Vector2<float>& aBoxPosition, const Vector2<float>& aBoxDimensions, const Vector2<float>& aCirclePosition, const float& aCircleRadius);
	bool BoxVsPointIntersection(const Vector2<float>& aBoxPosition, const Vector2<float>& aBoxDimensions, const Vector2<float>& aPointPosition);

	bool CircleVsCircleIntersection(const Vector2<float>& aFirstCirclePosition, const float& aFirstCircleRadius, const Vector2<float>& aSecondCirclePosition, const float& aSecondCircleRadius);
	bool CircleVsPointIntersection(const Vector2<float>& aCirclePosition, const float& aCircleRadius, const Vector2<float>& aPointPosition);

	bool PointVsPointIntersection(const Vector2<float>& aFirstPoint, const Vector2<float>& aSecondPoint);
};

#endif