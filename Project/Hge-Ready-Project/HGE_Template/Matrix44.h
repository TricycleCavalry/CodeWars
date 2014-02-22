#ifndef _MATRIX44_HEADER_
#define _MATRIX44_HEADER_

#include "Vector.h"


template<typename Type>
class Matrix33;
template<typename Type>
class Matrix44
{
public:
	Matrix44();
	Matrix44(Matrix33<Type> aMatrix);
	~Matrix44();

	static Matrix44 CreateRotateAroundX(Type aAngleInRadians);
	static Matrix44 CreateRotateAroundY(Type aAngleInRadians);
	static Matrix44 CreateRotateAroundZ(Type aAngleInRadians);
	void CreateProjectionMatrixLH(Type aNearZ, Type aFarZ, Type aAspectRatio,Type aFovAngle);
	static Matrix44 Identity();

	void Transpose();
	Matrix44 GetTranspose();

	Matrix33<Type> Get33() const;

	void SetPosition(Vector3<Type> aPosition);
	Vector3<Type> GetPosition() const;

	Type& operator[](int aElement);

	Matrix44 operator+(const Type aNumber) const;
	Matrix44 operator-(const Type aNumber) const;

	Matrix44 operator*(const Matrix44& aMatrix) const;
	Matrix44& operator*=(const Matrix44& aMatrix);
	bool operator==(const Matrix44& aMatrix) const;
	Matrix44& operator=(const Matrix44& aMatrix);

	Matrix44 operator*(const Matrix33<Type>& aMatrix) const;
	Matrix44& operator*=(const Matrix33<Type>& aMatrix);

	Vector4<Type> operator*(const Vector4<Type>& aVector) const;

	Type myMatrix[4*4];
};

	//Constructors and Destructors//
//----------------------------------------//

template<typename Type>
Matrix44<Type>::Matrix44()
{
	memset(&myMatrix,0,sizeof(myMatrix));
	myMatrix[0] = 1;
	myMatrix[5] = 1;
	myMatrix[10] = 1;
	myMatrix[15] = 1;
}

template<typename Type>
Matrix44<Type>::Matrix44(Matrix33<Type> aMatrix)
{
	myMatrix[0]	= aMatrix.myMatrix[0];
	myMatrix[1]	= aMatrix.myMatrix[1];
	myMatrix[2]	= aMatrix.myMatrix[2];
	myMatrix[3]	= 0;
	myMatrix[4]	= aMatrix.myMatrix[3];
	myMatrix[5]	= aMatrix.myMatrix[4];
	myMatrix[6]	= aMatrix.myMatrix[5];
	myMatrix[7]	= 0;
	myMatrix[8]	= aMatrix.myMatrix[6];
	myMatrix[9]	= aMatrix.myMatrix[7];
	myMatrix[10]	= aMatrix.myMatrix[8];
	myMatrix[11]	= 0;
	myMatrix[12]	= 0;
	myMatrix[13]	= 0;
	myMatrix[14]	= 0;
	myMatrix[15]	= 1;
}

template<typename Type>
Matrix44<Type>::~Matrix44()
{
}

				//Functions//
//----------------------------------------//

template<typename Type>
Matrix44<Type> Matrix44<Type>::CreateRotateAroundX(Type aAngleInRadians)
{
	Matrix44<Type> returnMatrix;
	memset(&returnMatrix,0,sizeof(Type)*16);
	returnMatrix.myMatrix[0] = 1;

	returnMatrix.myMatrix[5] = cos(aAngleInRadians);
	returnMatrix.myMatrix[6] = -sin(aAngleInRadians);

	returnMatrix.myMatrix[9] = sin(aAngleInRadians);
	returnMatrix.myMatrix[10] = cos(aAngleInRadians);

	returnMatrix.myMatrix[15] = 1;

	return returnMatrix;
}

template<typename Type>
Matrix44<Type> Matrix44<Type>::CreateRotateAroundY(Type aAngleInRadians)
{
	Matrix44<Type> returnMatrix;
	memset(&returnMatrix,0,sizeof(Type)*16);
	returnMatrix.myMatrix[4] = 1;

	returnMatrix.myMatrix[0] = cos(aAngleInRadians);
	returnMatrix.myMatrix[2] = -sin(aAngleInRadians);

	returnMatrix.myMatrix[8] = sin(aAngleInRadians);
	returnMatrix.myMatrix[10] = cos(aAngleInRadians);

	returnMatrix.myMatrix[15] = 1;

	return returnMatrix;
}


template<typename Type>
Matrix44<Type> Matrix44<Type>::CreateRotateAroundZ(Type aAngleInRadians)
{
	Matrix44<Type> returnMatrix;
	memset(&returnMatrix,0,sizeof(Type)*16);
	returnMatrix.myMatrix[8] = 1;

	returnMatrix.myMatrix[0] = cos(aAngleInRadians);
	returnMatrix.myMatrix[1] = -sin(aAngleInRadians);

	returnMatrix.myMatrix[4] = sin(aAngleInRadians);
	returnMatrix.myMatrix[5] = cos(aAngleInRadians);
	
	returnMatrix.myMatrix[15] = 1;

	return returnMatrix;
}

template<class Type>
void Matrix44<Type>::CreateProjectionMatrixLH(Type aNearZ, Type aFarZ, Type aAspectRatio,Type aFovAngle)
{
	Type    SinFov;
	Type    CosFov;
	Type    Height;
	Type    Width;

	SinFov = sin(0.5f * aFovAngle);
	CosFov = cos(0.5f * aFovAngle);
	
	Height = CosFov / SinFov;
	Width = Height / aAspectRatio;

	Type scaling = aFarZ / (aFarZ - aNearZ);

	myMatrix[0] = Width;
	/*myMatrix[1] = 0.0f;
	myMatrix[2] = 0.0f;
	myMatrix[3] = 0.0f;

	myMatrix[4] = 0.0f;*/
	myMatrix[5] = Height;
	/*myMatrix[6] = 0.0f;
	myMatrix[7] = 0.0f;

	myMatrix[8] = 0.0f;
	myMatrix[9] = 0.0f;*/
	myMatrix[10] = scaling;
	myMatrix[11] = -scaling * aNearZ;

	/*myMatrix[12] = 0.0f;
	myMatrix[13] = 0.0f;*/
	myMatrix[14] = 1.0f;
	myMatrix[15] = 0.0f;
}

template<typename Type>
void Matrix44<Type>::Transpose()
{
	*this = GetTranspose();
}

template<typename Type>
Matrix44<Type> Matrix44<Type>::GetTranspose()
{
	Matrix44<Type> newMatrix = *this;
	newMatrix.myMatrix[1] = myMatrix[4];
	newMatrix.myMatrix[2] = myMatrix[8];
	newMatrix.myMatrix[3] = myMatrix[12];
	newMatrix.myMatrix[4] = myMatrix[1];
	newMatrix.myMatrix[6] = myMatrix[9];
	newMatrix.myMatrix[7] = myMatrix[13];
	newMatrix.myMatrix[8] = myMatrix[2];
	newMatrix.myMatrix[9] = myMatrix[6];
	newMatrix.myMatrix[11] = myMatrix[14];
	newMatrix.myMatrix[12] = myMatrix[3];
	newMatrix.myMatrix[13] = myMatrix[7];
	newMatrix.myMatrix[14] = myMatrix[11];
	return newMatrix;
}

template<typename Type>
Matrix33<Type> Matrix44<Type>::Get33() const
{
	Matrix33<Type> returnMatrix;
	for(int i=0;i<9;i++)
	{
		returnMatrix[i] = myMatrix[i/3+i];
	}
	return returnMatrix;
}

template<typename Type>
Matrix44<Type> Matrix44<Type>::Identity()
{
	Matrix44<Type> returnMatrix;
	memset(&returnMatrix,0,sizeof(returnMatrix));
	returnMatrix.myMatrix[0] = 1;
	returnMatrix.myMatrix[5] = 1;
	returnMatrix.myMatrix[10] = 1;
	returnMatrix.myMatrix[15] = 1;
	return returnMatrix;
}

template<typename Type>
void Matrix44<Type>::SetPosition(Vector3<Type> aPosition)
{
	myMatrix[3] = aPosition.x; 
	myMatrix[7] = aPosition.y; 
	myMatrix[11] = aPosition.z; 
}

template<typename Type>
Vector3<Type> Matrix44<Type>::GetPosition() const
{
	return Vector3<Type>(myMatrix[3],myMatrix[7],myMatrix[11]);
}

				//Operators//
//----------------------------------------//

template <typename Type>
Type& Matrix44<Type>::operator[](int aElement)
{
	return myMatrix[aElement];
}

template<typename Type>
Matrix44<Type> Matrix44<Type>::operator+(const Type aNumber) const
{
	Matrix44<Type> returnMatrix = *this;
	for(int i=0;i<16;i++)
	{
		returnMatrix.myMatrix[i] += aNumber;
	}
	return returnMatrix;
}

template<typename Type>
Matrix44<Type> Matrix44<Type>::operator-(const Type aNumber) const
{
	Matrix44<Type> returnMatrix = *this;
	for(int i=0;i<16;i++)
	{
		returnMatrix.myMatrix[i] -= aNumber;
	}
	return returnMatrix;
}

template<typename Type>
Matrix44<Type> Matrix44<Type>::operator*(const Matrix44<Type>& aMatrix) const
{
	Matrix44<Type> returnMatrix = *this;
	returnMatrix.myMatrix[0 ] = myMatrix[0 ]*aMatrix.myMatrix[0]+myMatrix[1 ]*aMatrix.myMatrix[4]+myMatrix[2 ]*aMatrix.myMatrix[8 ]+myMatrix[3 ]*aMatrix.myMatrix[12];
	returnMatrix.myMatrix[1 ] = myMatrix[0 ]*aMatrix.myMatrix[1]+myMatrix[1 ]*aMatrix.myMatrix[5]+myMatrix[2 ]*aMatrix.myMatrix[9 ]+myMatrix[3 ]*aMatrix.myMatrix[13];
	returnMatrix.myMatrix[2 ] = myMatrix[0 ]*aMatrix.myMatrix[2]+myMatrix[1 ]*aMatrix.myMatrix[6]+myMatrix[2 ]*aMatrix.myMatrix[10]+myMatrix[3 ]*aMatrix.myMatrix[14];
	returnMatrix.myMatrix[3 ] = myMatrix[0 ]*aMatrix.myMatrix[3]+myMatrix[1 ]*aMatrix.myMatrix[7]+myMatrix[2 ]*aMatrix.myMatrix[11]+myMatrix[3 ]*aMatrix.myMatrix[15];
	returnMatrix.myMatrix[4 ] = myMatrix[4 ]*aMatrix.myMatrix[0]+myMatrix[5 ]*aMatrix.myMatrix[4]+myMatrix[6 ]*aMatrix.myMatrix[8 ]+myMatrix[7 ]*aMatrix.myMatrix[12];
	returnMatrix.myMatrix[5 ] = myMatrix[4 ]*aMatrix.myMatrix[1]+myMatrix[5 ]*aMatrix.myMatrix[5]+myMatrix[6 ]*aMatrix.myMatrix[9 ]+myMatrix[7 ]*aMatrix.myMatrix[13];
	returnMatrix.myMatrix[6 ] = myMatrix[4 ]*aMatrix.myMatrix[2]+myMatrix[5 ]*aMatrix.myMatrix[6]+myMatrix[6 ]*aMatrix.myMatrix[10]+myMatrix[7 ]*aMatrix.myMatrix[14];
	returnMatrix.myMatrix[7 ] = myMatrix[4 ]*aMatrix.myMatrix[3]+myMatrix[5 ]*aMatrix.myMatrix[7]+myMatrix[6 ]*aMatrix.myMatrix[11]+myMatrix[7 ]*aMatrix.myMatrix[15];
	returnMatrix.myMatrix[8 ] = myMatrix[8 ]*aMatrix.myMatrix[0]+myMatrix[9 ]*aMatrix.myMatrix[4]+myMatrix[10]*aMatrix.myMatrix[8 ]+myMatrix[11]*aMatrix.myMatrix[12];
	returnMatrix.myMatrix[9 ] = myMatrix[8 ]*aMatrix.myMatrix[1]+myMatrix[9 ]*aMatrix.myMatrix[5]+myMatrix[10]*aMatrix.myMatrix[9 ]+myMatrix[11]*aMatrix.myMatrix[13];
	returnMatrix.myMatrix[10] = myMatrix[8 ]*aMatrix.myMatrix[2]+myMatrix[9 ]*aMatrix.myMatrix[6]+myMatrix[10]*aMatrix.myMatrix[10]+myMatrix[11]*aMatrix.myMatrix[14];
	returnMatrix.myMatrix[11] = myMatrix[8 ]*aMatrix.myMatrix[3]+myMatrix[9 ]*aMatrix.myMatrix[7]+myMatrix[10]*aMatrix.myMatrix[11]+myMatrix[11]*aMatrix.myMatrix[15];
	returnMatrix.myMatrix[12] = myMatrix[12]*aMatrix.myMatrix[0]+myMatrix[13]*aMatrix.myMatrix[4]+myMatrix[14]*aMatrix.myMatrix[8 ]+myMatrix[15]*aMatrix.myMatrix[12];
	returnMatrix.myMatrix[13] = myMatrix[12]*aMatrix.myMatrix[1]+myMatrix[13]*aMatrix.myMatrix[5]+myMatrix[14]*aMatrix.myMatrix[9 ]+myMatrix[15]*aMatrix.myMatrix[13];
	returnMatrix.myMatrix[14] = myMatrix[12]*aMatrix.myMatrix[2]+myMatrix[13]*aMatrix.myMatrix[6]+myMatrix[14]*aMatrix.myMatrix[10]+myMatrix[15]*aMatrix.myMatrix[14];
	returnMatrix.myMatrix[15] = myMatrix[12]*aMatrix.myMatrix[3]+myMatrix[13]*aMatrix.myMatrix[7]+myMatrix[14]*aMatrix.myMatrix[11]+myMatrix[15]*aMatrix.myMatrix[15];
	return returnMatrix;
}

template<typename Type>
Matrix44<Type>& Matrix44<Type>::operator*=(const Matrix44<Type>& aMatrix)
{
	*this = (*this)*aMatrix;
	return *this;
}

template<typename Type>
Matrix44<Type>& Matrix44<Type>::operator=(const Matrix44<Type>& aMatrix)
{
	for(int i=0;i<16;i++)
	{
		myMatrix[i] = aMatrix.myMatrix[i];
	}
	return *this;
}

template<typename Type>
bool Matrix44<Type>::operator==(const Matrix44<Type>& aMatrix) const
{
	for(int i=0;i<16;i++)
	{
		if(myMatrix[i] != aMatrix.myMatrix[i])
		{
			return false;
		}
	}
	return true;
}

template<typename Type>
Matrix44<Type> Matrix44<Type>::operator*(const Matrix33<Type>& aMatrix) const
{
	Matrix44<Type> returnMatrix = *this;

	returnMatrix.myMatrix[0 ] = myMatrix[0]*aMatrix.myMatrix[0]+myMatrix[1]*aMatrix.myMatrix[3]+myMatrix[2 ]*aMatrix.myMatrix[6];
	returnMatrix.myMatrix[1 ] = myMatrix[0]*aMatrix.myMatrix[1]+myMatrix[1]*aMatrix.myMatrix[4]+myMatrix[2 ]*aMatrix.myMatrix[7];
	returnMatrix.myMatrix[2 ] = myMatrix[0]*aMatrix.myMatrix[2]+myMatrix[1]*aMatrix.myMatrix[5]+myMatrix[2 ]*aMatrix.myMatrix[8];

	returnMatrix.myMatrix[4 ] = myMatrix[4]*aMatrix.myMatrix[0]+myMatrix[5]*aMatrix.myMatrix[3]+myMatrix[6 ]*aMatrix.myMatrix[6];
	returnMatrix.myMatrix[5 ] = myMatrix[4]*aMatrix.myMatrix[1]+myMatrix[5]*aMatrix.myMatrix[4]+myMatrix[6 ]*aMatrix.myMatrix[7];
	returnMatrix.myMatrix[6 ] = myMatrix[4]*aMatrix.myMatrix[2]+myMatrix[5]*aMatrix.myMatrix[5]+myMatrix[6 ]*aMatrix.myMatrix[8];

	returnMatrix.myMatrix[8 ] = myMatrix[8]*aMatrix.myMatrix[0]+myMatrix[9]*aMatrix.myMatrix[3]+myMatrix[10]*aMatrix.myMatrix[6];
	returnMatrix.myMatrix[9 ] = myMatrix[8]*aMatrix.myMatrix[1]+myMatrix[9]*aMatrix.myMatrix[4]+myMatrix[10]*aMatrix.myMatrix[7];
	returnMatrix.myMatrix[10] = myMatrix[8]*aMatrix.myMatrix[2]+myMatrix[9]*aMatrix.myMatrix[5]+myMatrix[10]*aMatrix.myMatrix[8];

	return returnMatrix;
}

template<typename Type>
Matrix44<Type>& Matrix44<Type>::operator*=(const Matrix33<Type>& aMatrix)
{
	*this = (*this)*aMatrix;
	return *this;
}

template<typename Type>
Vector4<Type> Matrix44<Type>::operator*(const Vector4<Type>& aVector) const
{
	Vector4<Type> returnVector(aVector);
	returnVector.x = myMatrix[0]*aVector.x + myMatrix[1]*aVector.y + myMatrix[2]*aVector.z + myMatrix[3]*aVector.w;
	returnVector.y = myMatrix[4]*aVector.x + myMatrix[5]*aVector.y + myMatrix[6]*aVector.z + myMatrix[7]*aVector.w;
	returnVector.z = myMatrix[8]*aVector.x + myMatrix[9]*aVector.y + myMatrix[10]*aVector.z + myMatrix[11]*aVector.w;
	returnVector.w = myMatrix[12]*aVector.x + myMatrix[13]*aVector.y + myMatrix[14]*aVector.z + myMatrix[15]*aVector.w;
	return returnVector;
}

#endif