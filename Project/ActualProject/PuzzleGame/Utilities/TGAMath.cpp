#include "TGAMath.h"

//#include "Vector.h"
//using namespace TGAMath;
//
//float TGAMath::ToRadians(const float& aDegree)
//{
//	return aDegree * PI/180.f;
//}
//float TGAMath::ToDegrees(const float& aRadian)
//{
//	return aRadian * 180.f/PI;
//}
//float TGAMath::randf(const float& aFloat)
//{
//	return static_cast<float>(rand()%static_cast<int>(aFloat));
//}
//float TGAMath::Floor(const float& aFloat,unsigned int aNumDecimal)
//{
//	double numDecimal = pow(10,aNumDecimal);
//	float decimals = aFloat - static_cast<int>(aFloat);
//	
//	decimals *= numDecimal;
//	int decimalInt = static_cast<int>(decimals);
//	decimals = decimalInt;
//	decimals /= numDecimal;
//	//decimals = static_cast<float>(static_cast<int>(test)/numDecimal);
//
//	return static_cast<int>(aFloat) + decimals;
//
//}
//float TGAMath::Saturate(const float& aFloat)
//{
//	float returnFloat = aFloat;
//	if(returnFloat > 1.f)
//	{
//		returnFloat  = 1.f;
//	}
//	else if(returnFloat < 0.f)
//	{
//		returnFloat = 0.f;
//	}
//	return returnFloat;
//}
//
//float TGAMath::Absolute( const float &aFloat )
//{
//	if( aFloat < 0.f )
//	{
//		return -aFloat;
//	}
//	return aFloat;
//}
//	
//float TGAMath::RandomMinMaxFloat( const float aMinValue, const float aMaxValue )
//{
//	float a = abs(aMaxValue);
//	float b = abs(aMinValue);
//	if(  a != b )
//	{
//		return ( aMinValue + static_cast<float>(rand()%static_cast<int>(aMaxValue-aMinValue)) );
//	}
//	if(a == 0)
//	{
//		return 0;
//	}
//	return ( aMinValue + static_cast<float>(rand()%static_cast<int>(aMaxValue-aMinValue+1)) );
//}
//
//Vector2f TGAMath::RandomMinMaxVector( const Vector2f &aMinVector, const Vector2f &aMaxVector )
//{
//	Vector2f returnVector;
//
//	returnVector.x = RandomMinMaxFloat( aMinVector.x, aMaxVector.x );
//	returnVector.y = RandomMinMaxFloat( aMinVector.y, aMaxVector.y );
//
//	return returnVector;
//}
//Vector3f TGAMath::RandomMinMaxVector( const Vector3f &aMinVector, const Vector3f &aMaxVector )
//{
//	Vector3f returnVector;
//
//	returnVector.x = RandomMinMaxFloat( aMinVector.x, aMaxVector.x );
//	returnVector.y = RandomMinMaxFloat( aMinVector.y, aMaxVector.y );
//	returnVector.z = RandomMinMaxFloat( aMinVector.z, aMaxVector.z );
//
//	return returnVector;
//}
//
//float TGAMath::Lerp( const float aStartValue, const float aGoalValue, const float anAlpha )
//{
//	return aStartValue+(aGoalValue-aStartValue)*anAlpha;
//}