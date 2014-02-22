#ifndef _MATH_H_
#define _MATH_H_


#define PI		3.14159265359f
#define PI_2	1.57079632679f

#include "Vector.h"

namespace TGAMath
{
	float ToRadians(const float& aDegree);
	float ToDegrees(const float& aRadian);

	float randf(const float& aFloat);

	float Floor(const float& aFloat,unsigned int aNumDecimal);

	float Saturate(const float& aFloat);

	float Absolute( const float &aFloat );
	
	float RandomMinMaxFloat( const float aMinValue, const float aMaxValue );

	Vector2f RandomMinMaxVector( const Vector2f &aMinVector, const Vector2f &aMaxVector );
	Vector3f RandomMinMaxVector( const Vector3f &aMinVector, const Vector3f &aMaxVector );

	float Lerp( const float aStartValue, const float aGoalValue, const float anAlpha );
};

using namespace TGAMath;
#endif