#ifndef _VECTOR4_HEADER_
#define _VECTOR4_HEADER_

#include "math.h"
#include <intrin.h>
#include "Vector3.h"

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
	Vector4(const Vector3<Type>& aVector3, Type aW);
	Vector4(const Vector3<Type>& aVector3);
	~Vector4();

	Type Length();
	Type Length2();
	void Normalize();
	const Vector4 GetNormalize() const;
	Type Dot(const Vector4& aVector4);
	
	void Set(const Type& aX, const Type& aY, const Type& aZ, const Type& aW);
	static Vector4 Lerp(const Vector4& aV1, const Vector4& aV2, Type anAlpha);

	Vector4& operator=(const Vector4& aVector4);
	bool operator==(const Vector4& aVector4) const;

	
	Vector4 operator+(const Vector4& aVector4) const;
	Vector4 operator-(const Vector4& aVector4) const;
	Vector4 operator*(const Vector4& aVector4) const;
	Vector4 operator/(const Vector4& aVector4) const;

	Vector4& operator+=(const Vector4& aVector4);
	Vector4& operator-=(const Vector4& aVector4);
	Vector4& operator*=(const Vector4& aVector4);
	Vector4& operator/=(const Vector4& aVector4);

	Vector4 operator*(const Type aNumber) const;
	Vector4 operator/(const Type aNumber) const;
	Vector4& operator*=(const Type aNumber);
	Vector4& operator/=(const Type aNumber);

	Vector4 operator*(const Matrix33<Type> aMatrix) const;
	Vector4& operator*=(const Matrix33<Type> aMatrix);
	Vector4 operator*(const Matrix44<Type> aMatrix) const;
	Vector4& operator*=(const Matrix44<Type> aMatrix);

	Vector4& operator=(const Vector3<Type> aVector);
	
	union
	{
		struct
		{
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
		struct
		{
			Vector3<Type> xyz;
			Type w;
		};
		struct
		{
			Vector2<Type> xy;
			Type z;
			Type w;
		};
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
Vector4<Type>::Vector4(const Vector3<Type>& aVector3, Type aW)
{
	myX = aVector3.x;
	myY = aVector3.y;
	myZ = aVector3.z;
	myW = aW;
}

template<typename Type>
Vector4<Type>::Vector4(const Vector3<Type>& aVector3)
{
	myX = aVector3.x;
	myY = aVector3.y;
	myZ = aVector3.z;
	myW = 0;
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
const Vector4<Type> Vector4<Type>::GetNormalize() const
{
	Vector4<Type> returnVector;
	returnVector = *this;
	returnVector /= returnVector.Length();

	return returnVector;
}

template<typename Type>
Type Vector4<Type>::Dot(const Vector4<Type>& aVector4)
{
	return myX*aVector4.myX+myY*aVector4.myY+myZ*aVector4.myZ+myW*aVector4.myW;
}

template<typename Type>
void Vector4<Type>::Set(const Type& aX, const Type& aY, const Type& aZ, const Type& aW)
{
	myX = aX;
	myY = aY;
	myZ = aZ;
	myW = aW;
}

template<typename Type>
Vector4<Type> Vector4<Type>::Lerp(const Vector4<Type>& aV1, const Vector4<Type>& aV2, Type anAlpha)
{
	return aV1+(aV2-aV1)*anAlpha;
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
bool Vector4<Type>::operator==(const Vector4<Type>& aVector4) const
{
	if(myX == aVector4.myX && myY == aVector4.myY && myZ == aVector4.myZ && myW == aVector4.myW)
	{
		return true;
	}
	return false;
}
template<typename Type>
Vector4<Type> Vector4<Type>::operator+(const Vector4<Type>& aVector4) const
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX += aVector4.myX;
	returnVector.myY += aVector4.myY;
	returnVector.myZ += aVector4.myZ;
	returnVector.myW += aVector4.myW;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator-(const Vector4<Type>& aVector4) const
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX -= aVector4.myX;
	returnVector.myY -= aVector4.myY;
	returnVector.myZ -= aVector4.myZ;
	returnVector.myW -= aVector4.myW;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator*(const Vector4<Type>& aVector4) const
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX *= aVector4.myX;
	returnVector.myY *= aVector4.myY;
	returnVector.myZ *= aVector4.myZ;
	returnVector.myW *= aVector4.myW;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator*(const Type aNumber) const
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX *= aNumber;
	returnVector.myY *= aNumber;
	returnVector.myZ *= aNumber;
	returnVector.myW *= aNumber;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator/(const Vector4<Type>& aVector4) const
{
	Vector4<Type> returnVector(myX,myY,myZ,myW);
	returnVector.myX /= aVector4.myX;
	returnVector.myY /= aVector4.myY;
	returnVector.myZ /= aVector4.myZ;
	returnVector.myW /= aVector4.myW;
	return returnVector;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator/(const Type aNumber) const
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
Vector4<Type> Vector4<Type>::operator*(const Matrix33<Type> aMatrix) const
{
	return Vector4<Type>(myX*aMatrix[0]+myY*aMatrix[3]+myZ*aMatrix[6],
						myX*aMatrix[1]+myY*aMatrix[4]+myZ*aMatrix[7],
						myX*aMatrix[2]+myY*aMatrix[5]+myZ*aMatrix[8],
						myW);
}           

template<typename Type>
Vector4<Type>& Vector4<Type>::operator*=(const Matrix33<Type> aMatrix)
{
	*this = (*this)*aMatrix;
	return *this;
}

template<typename Type>
Vector4<Type> Vector4<Type>::operator*(const Matrix44<Type> aMatrix) const
{
	return Vector4<Type>(myX*aMatrix[0]+myY*aMatrix[4]+myZ*aMatrix[8]+myW*aMatrix[12],
						myX*aMatrix[1]+myY*aMatrix[5]+myZ*aMatrix[9 ]+myW*aMatrix[13],
						myX*aMatrix[2]+myY*aMatrix[6]+myZ*aMatrix[10]+myW*aMatrix[14],
						myX*aMatrix[3]+myY*aMatrix[7]+myZ*aMatrix[11]+myW*aMatrix[15]);
}

template<typename Type>
Vector4<Type>& Vector4<Type>::operator*=(const Matrix44<Type> aMatrix)
{
	*this = (*this)*aMatrix;
	return *this;
}

template<typename Type>
Vector4<Type>& Vector4<Type>::operator=(const Vector3<Type> aVector)
{
	myX = aVector.myX;
	myY = aVector.myY;
	myZ = aVector.myZ;
	myW = 0;

	return *this;
}

typedef Vector4<float> Vector4f;
typedef Vector4<int> Vector4i;

#endif