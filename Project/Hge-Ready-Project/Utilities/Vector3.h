#ifndef _VECTOR3_HEADER_
#define _VECTOR3_HEADER_
#include "math.h"

template<typename Type>
class Matrix33;

template<typename Type>
class Matrix44;

template<typename Type>
class Vector3
{
public:
	Vector3();
	Vector3(Type aX, Type aY, Type aZ);
	Vector3(const Vector3& aVector3);
	~Vector3();

	Type Length() const;
	Type Length2() const;
	void Normalize();
	Vector3 GetNormalize() const;
	Type Dot(const Vector3& aVector3) const;
	Vector3 Cross(const Vector3& aVector3) const;

	Vector3& operator=(const Vector3& aVector3);
	bool operator==(const Vector3& aVector3) const;

	static Vector3 Lerp(Vector3 aV1, Vector3 aV2, Type anAlpha);

	Vector3 operator+(const Vector3& aVector3) const;
	Vector3 operator-(const Vector3& aVector3) const;
	Vector3 operator*(const Vector3& aVector3) const;
	Vector3 operator/(const Vector3& aVector3) const;

	Vector3& operator+=(const Vector3& aVector3);
	Vector3& operator-=(const Vector3& aVector3);
	Vector3& operator*=(const Vector3& aVector3);
	Vector3& operator/=(const Vector3& aVector3);

	Vector3 operator*(const Type& aNumber) const;
	Vector3 operator/(const Type& aNumber) const;
	Vector3& operator*=(const Type& aNumber);
	Vector3& operator/=(const Type& aNumber);

	Vector3 operator+(const Type& aNumber) const;
	Vector3 operator-(const Type& aNumber) const;
	Vector3& operator+=(const Type& aNumber) const;
	Vector3& operator-=(const Type& aNumber) const;

	Vector3 operator*(const Matrix33<Type>& aMatrix) const;
	Vector3& operator*=(const Matrix33<Type>& aMatrix);
	Vector3 operator*(const Matrix44<Type>& aMatrix) const;
	Vector3& operator*=(const Matrix44<Type>& aMatrix);

	union
	{
		Type x;
		Type myX;
		Type r;
		Type myR;
	};
	union
	{
		Type y;
		Type myY;
		Type g;
		Type myG;
	};
	union
	{
		Type z;
		Type myZ;
		Type b;
		Type myB;
	};
};

	//Constructors and Destructors//
//----------------------------------------//

template<typename Type>
Vector3<Type>::Vector3()
{
	myX = 0;
	myY = 0;
	myZ = 0;
}

template<typename Type>
Vector3<Type>::Vector3(Type aX, Type aY, Type aZ)
{
	myX = aX;
	myY = aY;
	myZ = aZ;
}

template<typename Type>
Vector3<Type>::Vector3(const Vector3<Type>& aVector3)
{
	*this = aVector3;
}

template<typename Type>
Vector3<Type>::~Vector3()
{
}

				//Functions//
//----------------------------------------//

template<typename Type>
Type Vector3<Type>::Length() const
{
	return sqrt(Length2());
}

template<typename Type>
Type Vector3<Type>::Length2() const
{
	return myX*myX+myY*myY+myZ*myZ;
}

template<typename Type>
void Vector3<Type>::Normalize()
{
	float vectorLength = Length();
	myX /= vectorLength;
	myY /= vectorLength;
	myZ /= vectorLength;
}

template<typename Type>
Vector3<Type> Vector3<Type>::GetNormalize() const
{
	Vector3<Type> returnVector(*this);
	float vectorLength = Length();

	returnVector /= vectorLength;
	
	return returnVector;
}

template<typename Type>
Type Vector3<Type>::Dot(const Vector3<Type>& aVector3) const
{
	return myX*aVector3.myX+myY*aVector3.myY+myZ*aVector3.myZ;
}

template<typename Type>
Vector3<Type> Vector3<Type>::Cross(const Vector3<Type>& aVector3) const
{
	Vector3<Type> returnVector;
	returnVector.myX = myY*aVector3.myZ-myZ*aVector3.myY;
	returnVector.myY = myZ*aVector3.myX-myX*aVector3.myZ;
	returnVector.myZ = myX*aVector3.myY-myY*aVector3.myX;
	return returnVector;
}

template<typename Type>
Vector3<Type> Vector3<Type>::Lerp(Vector3<Type> aV1, Vector3<Type> aV2, Type anAlpha)
{
	return aV1+(aV2-aV1)*anAlpha;
}

				//Operators//
//----------------------------------------//

template<typename Type>
Vector3<Type>& Vector3<Type>::operator=(const Vector3<Type>& aVector3)
{
	myX = aVector3.myX;
	myY = aVector3.myY;
	myZ = aVector3.myZ;
	return *this;
}

template<typename Type>
bool Vector3<Type>::operator==(const Vector3<Type>& aVector3) const
{
	if(myX == aVector3.myX && myY == aVector3.myY && myZ == aVector3.myZ)
	{
		return true;
	}
	return false;
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator+(const Vector3<Type>& aVector3) const
{
	Vector3<Type> returnVector(myX,myY,myZ);
	returnVector.myX += aVector3.myX;
	returnVector.myY += aVector3.myY;
	returnVector.myZ += aVector3.myZ;
	return returnVector;
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator-(const Vector3<Type>& aVector3) const
{
	Vector3<Type> returnVector(myX,myY,myZ);
	returnVector.myX -= aVector3.myX;
	returnVector.myY -= aVector3.myY;
	returnVector.myZ -= aVector3.myZ;
	return returnVector;
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator*(const Vector3<Type>& aVector3) const
{
	Vector3<Type> returnVector(myX,myY,myZ);
	returnVector.myX *= aVector3.myX;
	returnVector.myY *= aVector3.myY;
	returnVector.myZ *= aVector3.myZ;
	return returnVector;
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator*(const Type& aNumber) const
{
	Vector3<Type> returnVector(myX,myY,myZ);
	returnVector.myX *= aNumber;
	returnVector.myY *= aNumber;
	returnVector.myZ *= aNumber;
	return returnVector;
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator/(const Vector3<Type>& aVector3) const
{
	Vector3<Type> returnVector(myX,myY,myZ);
	returnVector.myX /= aVector3.myX;
	returnVector.myY /= aVector3.myY;
	returnVector.myZ /= aVector3.myZ;
	return returnVector;
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator/(const Type& aNumber) const
{
	Vector3<Type> returnVector(myX,myY,myZ);
	returnVector.myX /= aNumber;
	returnVector.myY /= aNumber;
	returnVector.myZ /= aNumber;
	return returnVector;
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator+=(const Vector3<Type>& aVector3)
{
	myX += aVector3.myX;
	myY += aVector3.myY;
	myZ += aVector3.myZ;
	return *this;
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator-=(const Vector3<Type>& aVector3)
{
	myX -= aVector3.myX;
	myY -= aVector3.myY;
	myZ -= aVector3.myZ;
	return *this;
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator*=(const Vector3<Type>& aVector3)
{
	myX *= aVector3.myX;
	myY *= aVector3.myY;
	myZ *= aVector3.myZ;
	return *this;
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator*=(const Type& aNumber)
{
	myX *= aNumber;
	myY *= aNumber;
	myZ *= aNumber;
	return *this;
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator/=(const Vector3<Type>& aVector3)
{
	myX /= aVector3.myX;
	myY /= aVector3.myY;
	myZ /= aVector3.myZ;
	return *this;
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator/=(const Type& aNumber)
{
	myX /= aNumber;
	myY /= aNumber;
	myZ /= aNumber;
	return *this;
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator+(const Type& aNumber) const
{
	Vector3<Type> returnVector;
	returnVector.myX = myX+aNumber;
	returnVector.myY = myY+aNumber;
	returnVector.myZ = myZ+aNumber;
	return returnVector;
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator-(const Type& aNumber) const
{
	Vector3<Type> returnVector;
	returnVector.myX = myX-aNumber;
	returnVector.myY = myY-aNumber;
	returnVector.myZ = myZ-aNumber;
	return returnVector;
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator+=(const Type& aNumber) const
{
	return *this = *this+aNumber;
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator-=(const Type& aNumber) const
{
	return *this = *this-aNumber;
}


template<typename Type>
Vector3<Type> Vector3<Type>::operator*(const Matrix33<Type>& aMatrix) const
{
	return Vector3<Type>(myX*aMatrix.myMatrix[0]+myY*aMatrix.myMatrix[3]+myZ*aMatrix.myMatrix[6],
						myX*aMatrix.myMatrix[1]+myY*aMatrix.myMatrix[4]+myZ*aMatrix.myMatrix[7],
						myX*aMatrix.myMatrix[2]+myY*aMatrix.myMatrix[5]+myZ*aMatrix.myMatrix[8]);
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator*=(const Matrix33<Type>& aMatrix)
{
	*this = (*this)*aMatrix;
	return *this;
}

template<typename Type>
Vector3<Type> Vector3<Type>::operator*(const Matrix44<Type>& aMatrix) const
{
	return (*this)*aMatrix.Get33();
}

template<typename Type>
Vector3<Type>& Vector3<Type>::operator*=(const Matrix44<Type>& aMatrix)
{
	*this = (*this)*aMatrix.Get33();
	return *this;
}

#endif