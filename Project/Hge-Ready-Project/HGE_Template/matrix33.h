#ifndef _MATRIX33_HEADER_
#define _MATRIX33_HEADER_

#include <string.h>
#include "Matrix44.h"

template<typename Type>
class Matrix33
{
public:
	Matrix33();
	Matrix33(const Matrix44<Type>& aMatrix);
	~Matrix33();

	static Matrix33 CreateRotateAroundX(Type aAngleInRadians);
	static Matrix33 CreateRotateAroundY(Type aAngleInRadians);
	static Matrix33 CreateRotateAroundZ(Type aAngleInRadians);
	static Matrix33 Identity();

	void SetRotation2D(Type aAngleInRadians);

	void Transpose();
	Matrix33 GetTranspose();

	void SetPosition(Vector2<Type> aPosition);
	Vector2<Type> GetPosition();

	Type& operator[](int aElement);

	Matrix33 operator+(const Type aNumber);
	Matrix33 operator-(const Type aNumber);

	Matrix33 operator*(const Matrix33& aMatrix);
	Matrix33& operator*=(const Matrix33& aMatrix);
	bool operator==(const Matrix33& aMatrix);
	Matrix33& operator=(const Matrix33& aMatrix);

	Matrix33 operator*(const Matrix44<Type>& aMatrix);
	Matrix33& operator*=(const Matrix44<Type>& aMatrix);
	
	Vector3<Type> operator*(const Vector3<Type>& aVector);

	Type myMatrix[3*3];
};

	//Constructors and Destructors//
//----------------------------------------//

template<typename Type>
Matrix33<Type>::Matrix33()
{
	memset(&myMatrix,0,sizeof(Type)*9);
	myMatrix[0] = 1;
	myMatrix[4] = 1;
	myMatrix[8] = 1;
}

template<typename Type>
Matrix33<Type>::Matrix33(const Matrix44<Type>& aMatrix)
{
	for(int i=0;i<9;i++)
	{
		if(i<3)
		{
			myMatrix[i] = aMatrix.myMatrix[i];
		}
		else if(i<6)
		{
			myMatrix[i] = aMatrix.myMatrix[i+1];
		}
		else
		{
			myMatrix[i] = aMatrix.myMatrix[i+2];
		}
	}
}

template<typename Type>
Matrix33<Type>::~Matrix33()
{
}

				//Functions//
//----------------------------------------//

template<typename Type>
Matrix33<Type> Matrix33<Type>::CreateRotateAroundX(Type aAngleInRadians)
{
	Matrix33<Type> returnMatrix;
	memset(&returnMatrix,0,sizeof(Type)*9);
	returnMatrix.myMatrix[0] = 1;

	returnMatrix.myMatrix[4] = cos(aAngleInRadians);
	returnMatrix.myMatrix[5] = -sin(aAngleInRadians);

	returnMatrix.myMatrix[7] = sin(aAngleInRadians);
	returnMatrix.myMatrix[8] = cos(aAngleInRadians);
	return returnMatrix;
}

template<typename Type>
Matrix33<Type> Matrix33<Type>::CreateRotateAroundY(Type aAngleInRadians)
{
	Matrix33<Type> returnMatrix;
	memset(&returnMatrix,0,sizeof(Type)*9);
	returnMatrix.myMatrix[4] = 1;

	returnMatrix.myMatrix[0] = cos(aAngleInRadians);
	returnMatrix.myMatrix[2] = -sin(aAngleInRadians);

	returnMatrix.myMatrix[6] = sin(aAngleInRadians);
	returnMatrix.myMatrix[8] = cos(aAngleInRadians);
	return returnMatrix;
}


template<typename Type>
Matrix33<Type> Matrix33<Type>::CreateRotateAroundZ(Type aAngleInRadians)
{
	Matrix33<Type> returnMatrix;
	memset(&returnMatrix,0,sizeof(Type)*9);
	returnMatrix.myMatrix[8] = 1;

	returnMatrix.myMatrix[0] = cos(aAngleInRadians);
	returnMatrix.myMatrix[1] = -sin(aAngleInRadians);

	returnMatrix.myMatrix[3] = sin(aAngleInRadians);
	returnMatrix.myMatrix[4] = cos(aAngleInRadians);
	return returnMatrix;
}

template<typename Type>
Matrix33<Type> Matrix33<Type>::Identity()
{
	Matrix33<Type> returnMatrix;
	memset(&returnMatrix,0,sizeof(Type)*9);
	myMatrix[0] = 1;
	myMatrix[4] = 1;
	myMatrix[8] = 1;
	return returnMatrix;
}

template<typename Type>
void Matrix33<Type>::SetRotation2D(Type aAngleInRadians)
{
	myMatrix[0] = cos(aAngleInRadians);
	myMatrix[1] = -sin(aAngleInRadians);

	myMatrix[3] = sin(aAngleInRadians);
	myMatrix[4] = cos(aAngleInRadians);
}

template<typename Type>
void Matrix33<Type>::Transpose()
{
	*this = GetTranspose();
}

template<typename Type>
Matrix33<Type> Matrix33<Type>::GetTranspose()
{
	Matrix33<Type> newMatrix = *this;
	newMatrix.myMatrix[1] = myMatrix[3];
	newMatrix.myMatrix[2] = myMatrix[6];
	newMatrix.myMatrix[3] = myMatrix[1];
	newMatrix.myMatrix[5] = myMatrix[7];
	newMatrix.myMatrix[6] = myMatrix[2];
	newMatrix.myMatrix[7] = myMatrix[5];
	return newMatrix;
}

template<typename Type>
void Matrix33<Type>::SetPosition(Vector2<Type> aPosition)
{
	myMatrix[2] = aPosition.x;
	myMatrix[5] = aPosition.y;
}

template<typename Type>
Vector2<Type> Matrix33<Type>::GetPosition()
{
	return Vector2<Type>(myMatrix[2],myMatrix[5]);
}

				//Operators//
//----------------------------------------//


template <typename Type>
Type& Matrix33<Type>::operator[](int aElement)
{
	return myMatrix[aElement];
}

template<typename Type>
Matrix33<Type> Matrix33<Type>::operator+(const Type aNumber)
{
	Matrix33<Type> returnMatrix = *this;
	for(int i=0;i<9;i++)
	{
		returnMatrix.myMatrix[i] += aNumber;
	}
	return returnMatrix;
}

template<typename Type>
Matrix33<Type> Matrix33<Type>::operator-(const Type aNumber)
{
	Matrix33<Type> returnMatrix = *this;
	for(int i=0;i<9;i++)
	{
		returnMatrix.myMatrix[i] -= aNumber;
	}
	return returnMatrix;
}

template<typename Type>
Matrix33<Type> Matrix33<Type>::operator*(const Matrix33<Type>& aMatrix)
{
	Matrix33<Type> returnMatrix = *this;
	returnMatrix.myMatrix[0] = myMatrix[0]*aMatrix.myMatrix[0]+myMatrix[1]*aMatrix.myMatrix[3]+myMatrix[2]*aMatrix.myMatrix[6];
	returnMatrix.myMatrix[1] = myMatrix[0]*aMatrix.myMatrix[1]+myMatrix[1]*aMatrix.myMatrix[4]+myMatrix[2]*aMatrix.myMatrix[7];
	returnMatrix.myMatrix[2] = myMatrix[0]*aMatrix.myMatrix[2]+myMatrix[1]*aMatrix.myMatrix[5]+myMatrix[2]*aMatrix.myMatrix[8];

	returnMatrix.myMatrix[3] = myMatrix[3]*aMatrix.myMatrix[0]+myMatrix[4]*aMatrix.myMatrix[3]+myMatrix[5]*aMatrix.myMatrix[6];
	returnMatrix.myMatrix[4] = myMatrix[3]*aMatrix.myMatrix[1]+myMatrix[4]*aMatrix.myMatrix[4]+myMatrix[5]*aMatrix.myMatrix[7];
	returnMatrix.myMatrix[5] = myMatrix[3]*aMatrix.myMatrix[2]+myMatrix[4]*aMatrix.myMatrix[5]+myMatrix[5]*aMatrix.myMatrix[8];

	returnMatrix.myMatrix[6] = myMatrix[6]*aMatrix.myMatrix[0]+myMatrix[7]*aMatrix.myMatrix[3]+myMatrix[8]*aMatrix.myMatrix[6];
	returnMatrix.myMatrix[7] = myMatrix[6]*aMatrix.myMatrix[1]+myMatrix[7]*aMatrix.myMatrix[4]+myMatrix[8]*aMatrix.myMatrix[7];
	returnMatrix.myMatrix[8] = myMatrix[6]*aMatrix.myMatrix[2]+myMatrix[7]*aMatrix.myMatrix[5]+myMatrix[8]*aMatrix.myMatrix[8];
	return returnMatrix;
}

template<typename Type>
Matrix33<Type>& Matrix33<Type>::operator*=(const Matrix33<Type>& aMatrix)
{
	*this = (*this)*aMatrix;
	return *this;
}

template<typename Type>
Matrix33<Type>& Matrix33<Type>::operator=(const Matrix33<Type>& aMatrix)
{
	for(int i=0;i<9;i++)
	{
		myMatrix[i] = aMatrix.myMatrix[i];
	}
	return *this;
}

template<typename Type>
bool Matrix33<Type>::operator==(const Matrix33<Type>& aMatrix)
{
	for(int i=0;i<9;i++)
	{
		if(myMatrix[i] != aMatrix.myMatrix[i])
		{
			return false;
		}
	}
	return true;
}

template<typename Type>
Matrix33<Type> Matrix33<Type>::operator*(const Matrix44<Type>& aMatrix)
{
	Matrix33<Type> returnMatrix = *this;
	returnMatrix.myMatrix[0] = myMatrix[0]*aMatrix.myMatrix[0]+myMatrix[1]*aMatrix.myMatrix[4]+myMatrix[2]*aMatrix.myMatrix[8];
	returnMatrix.myMatrix[1] = myMatrix[0]*aMatrix.myMatrix[1]+myMatrix[1]*aMatrix.myMatrix[5]+myMatrix[2]*aMatrix.myMatrix[9];
	returnMatrix.myMatrix[2] = myMatrix[0]*aMatrix.myMatrix[2]+myMatrix[1]*aMatrix.myMatrix[6]+myMatrix[2]*aMatrix.myMatrix[10];

	returnMatrix.myMatrix[3] = myMatrix[3]*aMatrix.myMatrix[0]+myMatrix[4]*aMatrix.myMatrix[4]+myMatrix[5]*aMatrix.myMatrix[8];
	returnMatrix.myMatrix[4] = myMatrix[3]*aMatrix.myMatrix[1]+myMatrix[4]*aMatrix.myMatrix[5]+myMatrix[5]*aMatrix.myMatrix[9];
	returnMatrix.myMatrix[5] = myMatrix[3]*aMatrix.myMatrix[2]+myMatrix[4]*aMatrix.myMatrix[6]+myMatrix[5]*aMatrix.myMatrix[10];

	returnMatrix.myMatrix[6] = myMatrix[6]*aMatrix.myMatrix[0]+myMatrix[7]*aMatrix.myMatrix[4]+myMatrix[8]*aMatrix.myMatrix[8];
	returnMatrix.myMatrix[7] = myMatrix[6]*aMatrix.myMatrix[1]+myMatrix[7]*aMatrix.myMatrix[5]+myMatrix[8]*aMatrix.myMatrix[9];
	returnMatrix.myMatrix[8] = myMatrix[6]*aMatrix.myMatrix[2]+myMatrix[7]*aMatrix.myMatrix[6]+myMatrix[8]*aMatrix.myMatrix[10];
	return returnMatrix;
}

template<typename Type>
Matrix33<Type>& Matrix33<Type>::operator*=(const Matrix44<Type>& aMatrix)
{
	*this = (*this)*aMatrix;
	return *this;
}

template<typename Type>
Vector3<Type> Matrix33<Type>::operator*(const Vector3<Type>& aVector)
{
	Vector3<Type> returnVector(aVector);
	returnVector.x = myMatrix[0]*aVector.x+myMatrix[1]*aVector.y+myMatrix[2]*aVector.z;
	returnVector.y = myMatrix[3]*aVector.x+myMatrix[4]*aVector.y+myMatrix[5]*aVector.z;
	returnVector.z = myMatrix[6]*aVector.x+myMatrix[7]*aVector.y+myMatrix[8]*aVector.z;
	return returnVector;
}

#endif