#ifndef _VECTOR2_HEADER_
#define _VECTOR2_HEADER_

#define _USE_MATH_DEFINES
#include "math.h"

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
	Vector2 operator+(const Vector2& aVector2) const;
	Vector2 operator-(const Vector2& aVector2) const;
	Vector2 operator*(const Vector2& aVector2) const;
	Vector2 operator*(const Type aNumber) const;
	Vector2 operator/(const Vector2& aVector2) const;
	Vector2 operator/(const Type aNumber) const;
	Vector2& operator+=(const Vector2& aVector2);
	Vector2& operator-=(const Vector2& aVector2);
	Vector2& operator*=(const Vector2& aVector2);
	Vector2& operator*=(const Type aNumber);
	Vector2& operator/=(const Vector2& aVector2);
	Vector2& operator/=(const Type aNumber);



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
	Type newY = x*sine-y*cosine;
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
Vector2<Type>& Vector2<Type>::operator-=(const Vector2<Type>& aVector2)
{
	myX -= aVector2.myX;
	myY -= aVector2.myY;
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

#endif