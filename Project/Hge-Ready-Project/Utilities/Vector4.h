#ifndef _VECTOR4_HEADER_
#define _VECTOR4_HEADER_

#include "math.h"

template<typename Type>
class Vector3;

template<typename Type>
class Matrix33;

template<typename Type>
class Matrix44;

template<typename Type>
class Vector4
{
public:
	Vector4();
	Vector4(Type aX, Type aY, Type aZ, Type aW);
	Vector4(const Vector4& aVector4);
	~Vector4();

	Type Length();
	Type Length2();
	void Normalize();
	Type Dot(const Vector4& aVector4);

	Vector4& operator=(const Vector4& aVector4);
	bool operator==(const Vector4& aVector4);

	Vector4 operator+(const Vector4& aVector4);
	Vector4 operator-(const Vector4& aVector4);
	Vector4 operator*(const Vector4& aVector4);
	Vector4 operator/(const Vector4& aVector4);

	Vector4& operator+=(const Vector4& aVector4);
	Vector4& operator-=(const Vector4& aVector4);
	Vector4& operator*=(const Vector4& aVector4);
	Vector4& operator/=(const Vector4& aVector4);

	Vector4 operator*(const Type aNumber);
	Vector4 operator/(const Type aNumber);
	Vector4& operator*=(const Type aNumber);
	Vector4& operator/=(const Type aNumber);

	Vector4 operator*(const Matrix33<Type> aMatrix);
	Vector4& operator*=(const Matrix33<Type> aMatrix);
	Vector4 operator*(const Matrix44<Type> aMatrix);
	Vector4& operator*=(const Matrix44<Type> aMatrix);

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
	union
	{
		Type w;
		Type myW;
		Type a;
		Type myA;
	};
};

	//Constructors and Destructors//
//----------------------------------------//

template<typename Type>
Vector4<Type>::Vector4()
{
	myX = 0;
	myY = 0;
	myZ = 0;
	myW = 0;
}

template<typename Type>
Vector4<Type>::Vector4(Type aX, Type aY, Type aZ, Type aW)
{
	myX = aX;
	myY = aY;
	myZ = aZ;
	myW = aW;
}

template<typename Type>
Vector4<Type>::Vector4(const Vector4<Type> &aVector4)
{
	*this = aVector4;
}

template<typename Type>
Vector4<Type>::~Vector4()
{
}

				//Functions//
//----------------------------------------//

template<typename Type>
Type Vector4<Type>::Length()
{
	return sqrt(Length2());
}

template<typename Type>
Type Vector4<Type>::Length2()
{
	return float(myX*myX+myY*myY+myZ*myZ+myW*myW);
}

template<typename Type>
void Vector4<Type>::Normalize()
{
	float vectorLength = Length();
	myX /= vectorLength;
	myY /= vectorLength;
	myZ /= vectorLength;
	myW /= vectorLength;
}

template<typename Type>
Type Vector4<Type>::Dot(const Vector4<Type>& aVector4)
{
	return myX*aVector4.myX+myY*aVector4.myY+myZ*aVector4.myZ+myW*aVector4.myW;
}

				//Operators//
//----------------------------------------//

template<typename Type>
Vector4<Type>& Vector4<Type>::operator=(const Vector4<Type>& aVector4)
{
	myX = aVector4.myX;
	myY = aVector4.myY;
	myZ = aVector4.myZ;
	myW = aVector4.myW;
	return *this;
}

template<typename Type>
bool Vector4<Type>::operator==(const Vector4<Type>& aVector4)
{
	if(myX == aVector4.myX && myY == aVector4.myY && myZ == aVector4.myZ && myW == aVector4.myW)
	{
		return true;
	}
	return false;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator+(const Vector4<Type>& aVector4)
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX += aVector4.myX;
	returnVector.myY += aVector4.myY;
	returnVector.myZ += aVector4.myZ;
	returnVector.myW += aVector4.myW;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator-(const Vector4<Type>& aVector4)
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX -= aVector4.myX;
	returnVector.myY -= aVector4.myY;
	returnVector.myZ -= aVector4.myZ;
	returnVector.myW -= aVector4.myW;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator*(const Vector4<Type>& aVector4)
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX *= aVector4.myX;
	returnVector.myY *= aVector4.myY;
	returnVector.myZ *= aVector4.myZ;
	returnVector.myW *= aVector4.myW;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator*(const Type aNumber)
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX *= aNumber;
	returnVector.myY *= aNumber;
	returnVector.myZ *= aNumber;
	returnVector.myW *= aNumber;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator/(const Vector4<Type>& aVector4)
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX /= aVector4.myX;
	returnVector.myY /= aVector4.myY;
	returnVector.myZ /= aVector4.myZ;
	returnVector.myW /= aVector4.myW;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator/(const Type aNumber)
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX /= aNumber;
	returnVector.myY /= aNumber;
	returnVector.myZ /= aNumber;
	returnVector.myW /= aNumber;
	return returnVector;
}

template<typename Type>
Vector4<Type>& Vector4<Type>::operator+=(const Vector4<Type>& aVector4)
{
	myX += aVector4.myX;
	myY += aVector4.myY;
	myZ += aVector4.myZ;
	myW += aVector4.myW;
	return *this;
}

template<typename Type>
Vector4<Type>& Vector4<Type>::operator-=(const Vector4<Type>& aVector4)
{
	myX -= aVector4.myX;
	myY -= aVector4.myY;
	myZ -= aVector4.myZ;
	myW -= aVector4.myW;
	return *this;
}

template<typename Type>
Vector4<Type>& Vector4<Type>::operator*=(const Vector4<Type>& aVector4)
{
	myX *= aVector4.myX;
	myY *= aVector4.myY;
	myZ *= aVector4.myZ;
	myW *= aVector4.myW;
	return *this;
}

template<typename Type>
Vector4<Type>& Vector4<Type>::operator*=(const Type aNumber)
{
	myX *= aNumber;
	myY *= aNumber;
	myZ *= aNumber;
	myW *= aNumber;
	return *this;
}

template<typename Type>
Vector4<Type>& Vector4<Type>::operator/=(const Vector4<Type>& aVector4)
{
	myX /= aVector4.myX;
	myY /= aVector4.myY;
	myZ /= aVector4.myZ;
	myW /= aVector4.myW;
	return *this;
}

template<typename Type>
Vector4<Type>& Vector4<Type>::operator/=(const Type aNumber)
{
	myX /= aNumber;
	myY /= aNumber;
	myZ /= aNumber;
	myW /= aNumber;
	return *this;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator*(const Matrix33<Type> aMatrix)
{
	return Vector4<Type>(myX*aMatrix[0]+myX*aMatrix[3]+myX*aMatrix[6],
						myY*aMatrix[1]+myY*aMatrix[4]+myY*aMatrix[7],
						myZ*aMatrix[2]+myZ*aMatrix[5]+myZ*aMatrix[8],
						myW);
}           

template<typename Type>
Vector4<Type>& Vector4<Type>::operator*=(const Matrix33<Type> aMatrix)
{
	*this = (*this)*aMatrix;
	return *this;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator*(const Matrix44<Type> aMatrix)
{
	return Vector4<Type>(myX*aMatrix[0]+myX*aMatrix[4]+myX*aMatrix[8]+myX*aMatrix[12],
						myY*aMatrix[1]+myY*aMatrix[5]+myY*aMatrix[9 ]+myY*aMatrix[13],
						myZ*aMatrix[2]+myZ*aMatrix[6]+myZ*aMatrix[10]+myZ*aMatrix[14],
						myW*aMatrix[3]+myW*aMatrix[7]+myW*aMatrix[11]+myW*aMatrix[15]);
}

template<typename Type>
Vector4<Type>& Vector4<Type>::operator*=(const Matrix44<Type> aMatrix)
{
	*this = (*this)*aMatrix;
	return *this;
}

#endif