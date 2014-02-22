#ifndef _VECTOR2_HEADER_
#define _VECTOR2_HEADER_

#define _USE_MATH_DEFINES
#include <math.h>


template<typename Type>
class Vector2
{
public:
	Vector2();
	Vector2(Type aX, Type aY);
	Vector2(const Vector2& aVector2);
	~Vector2();

	Type Length() const;
	Type Length2() const;
	void Normalize();
	Vector2 GetNormalize() const;
	Type Dot(const Vector2& aVector2) const;

	static Vector2<Type> Lerp( const Vector2<Type>& v1,const Vector2<Type>& v2,const Type& aAlpha);

	void Rotate(const Type& someDegrees);

	Vector2& operator=(const Vector2& aVector2);
	bool operator==(const Vector2& aVector2) const;
	bool operator!=(const Vector2& aVector2) const;
	Vector2 operator+(const Vector2& aVector2) const;
	Vector2 operator-(const Vector2& aVector2) const;
	Vector2 operator*(const Vector2& aVector2) const;
	Vector2 operator*(const Type aNumber) const;
	Vector2 operator/(const Vector2& aVector2) const;
	Vector2 operator/(const Type aNumber) const;
	Vector2& operator+=(const Vector2& aVector2);
	Vector2& operator+=(const Type aNumber);
	Vector2& operator-=(const Vector2& aVector2);
	Vector2& operator-=(const Type& aNumber);
	Vector2& operator*=(const Vector2& aVector2);
	Vector2& operator*=(const Type aNumber);
	Vector2& operator/=(const Vector2& aVector2);
	Vector2& operator/=(const Type aNumber);

	void Truncate(float aMaxLength);

	float GetDegreeAngleBetweenVectors( const Vector2 &aSecondVector );
	Type GetAngle();

	union
	{
		Type x;
		Type myX;
		Type r;
		Type myR;
		Type u;
	};
	union
	{
		Type y;
		Type myY;
		Type g;
		Type myG;
		Type v;
	};
};

	//Constructors and Destructors//
//----------------------------------------//

template<typename Type>
Vector2<Type>::Vector2()
{
	myX = 0;
	myY = 0;
}

template<typename Type>
Vector2<Type>::Vector2(Type aX, Type aY)
{
	myX = aX;
	myY = aY;
}

template<typename Type>
Vector2<Type>::Vector2(const Vector2<Type>& aVector2)
{
	*this = aVector2;
}

template<typename Type>
Vector2<Type>::~Vector2()
{
}

				//Functions//
//----------------------------------------//

template<typename Type>
Type Vector2<Type>::Length() const
{
	return sqrt(Length2());
}

template<typename Type>
Type Vector2<Type>::Length2() const
{
	return myX*myX+myY*myY;
}

template<typename Type>
void Vector2<Type>::Normalize()
{
	Type vectorLength = Length();
	myX /= vectorLength;
	myY /= vectorLength;
	
}

template<typename Type>
Vector2<Type> Vector2<Type>::GetNormalize() const
{
	Vector2<Type> returnVector(myX,myY);
	returnVector.Normalize();
	return returnVector;
}

template<typename Type>
Type Vector2<Type>::Dot(const Vector2<Type>& aVector2) const
{
	return myX*aVector2.myX+myY*aVector2.myY;
}

template <typename Type>
Vector2<Type> Vector2<Type>::Lerp( const Vector2<Type>& v1,const Vector2<Type>& v2,const Type& aAlpha)
{
	return(v1 + ((v2 - v1) * aAlpha));
}

template<typename Type>
void Vector2<Type>::Rotate(const Type& someDegrees)
{
	Type radians = static_cast<Type>(someDegrees*(M_PI/180));
	Type cosine = cos(radians);
	Type sine = sin(radians);

	Type newX = x*cosine-y*sine;
	Type newY = x*sine+y*cosine;
	x = newX;
	y = newY;
}

				//Operators//
//----------------------------------------//

template<typename Type>
Vector2<Type>& Vector2<Type>::operator=(const Vector2<Type>& aVector2)
{
	myX = aVector2.myX;
	myY = aVector2.myY;
	return *this;
}

template<typename Type>
bool Vector2<Type>::operator==(const Vector2<Type>& aVector2) const
{
	if(myX == aVector2.myX && myY == aVector2.myY)
	{
		return true;
	}
	return false;
}

template<typename Type>
bool Vector2<Type>::operator!=(const Vector2& aVector2) const
{
	if(myX != aVector2.myX || myY != aVector2.myY)
	{
		return true;
	}
	return false;
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator+(const Vector2<Type>& aVector2) const
{
	Vector2<Type> returnVector(x,y);
	returnVector.myX += aVector2.myX;
	returnVector.myY += aVector2.myY;
	return returnVector;
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator-(const Vector2<Type>& aVector2) const
{
	Vector2<Type> returnVector(x,y);
	returnVector.myX -= aVector2.myX;
	returnVector.myY -= aVector2.myY;
	return returnVector;
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator*(const Vector2<Type>& aVector2) const
{
	Vector2<Type> returnVector(myX,myY);
	returnVector.myX *= aVector2.myX;
	returnVector.myY *= aVector2.myY;
	return returnVector;
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator*(const Type aNumber) const
{
	Vector2<Type> returnVector(myX,myY);
	returnVector.myX *= aNumber;
	returnVector.myY *= aNumber;
	return returnVector;
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator/(const Vector2<Type>& aVector2) const
{
	Vector2<Type> returnVector(myX,y);
	returnVector.myX /= aVector2.myX;
	returnVector.myY /= aVector2.myY;
	return returnVector;
}

template<typename Type>
Vector2<Type> Vector2<Type>::operator/(const Type aNumber) const
{
	Vector2<Type> returnVector(myX,myY);
	returnVector.myX /= aNumber;
	returnVector.myY /= aNumber;
	return returnVector;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator+=(const Vector2<Type>& aVector2)
{
	myX += aVector2.myX;
	myY += aVector2.myY;
	return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator+=(const Type aNumber)
{
	myX += aNumber;
	myY += aNumber;
	return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator-=(const Vector2<Type>& aVector2)
{
	myX -= aVector2.myX;
	myY -= aVector2.myY;
	return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator-=(const Type& aNumber)
{
	myX -= aNumber;
	myY -= aNumber;
	return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator*=(const Vector2<Type>& aVector2)
{
	myX *= aVector2.myX;
	myY *= aVector2.myY;
	return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator*=(const Type aNumber)
{
	myX *= aNumber;
	myY *= aNumber;
	return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator/=(const Vector2<Type>& aVector2)
{
	myX /= aVector2.myX;
	myY /= aVector2.myY;
	return *this;
}

template<typename Type>
Vector2<Type>& Vector2<Type>::operator/=(const Type aNumber)
{
	myX /= aNumber;
	myY /= aNumber;
	return *this;
}

template<typename Type>
void Vector2<Type>::Truncate(float aMaxLength)
{
	float length2 = Length2();
	if(length2 > aMaxLength * aMaxLength  && length2 > 0)
	{
		Normalize();
		(*this) *= aMaxLength;
	}
}

template<typename Type>
float Vector2<Type>::GetDegreeAngleBetweenVectors( const Vector2 &aSecondVector )
{
	return ((atan2( myY - aSecondVector.myY, myX - aSecondVector.myX )*180)/3.14f);
}

template<typename Type>
Type Vector2<Type>::GetAngle()
{
	Vector2<Type> temp;
	temp.myX = myX;
	temp.myY = myY;
	Type returnTemp = atan2( temp.myY, temp.myX );

	return returnTemp;
}

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

#endif