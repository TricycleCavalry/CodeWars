#ifndef PLANE_HEADER
#define PLANE_HEADER

#include "Vector3.h"

template <typename DataType> class Plane
{
public:
	Plane(void);
	Plane(Vector3<DataType> aFirstPoint, Vector3<DataType> aSecondPoint, Vector3<DataType> aThirdPoint);
	Plane(const Vector3<DataType>& aPoint,const Vector3<DataType>& aNormal);
	
	void InitWith3Points(Vector3<DataType> aFirstPoint,Vector3<DataType> aSecondPoint,Vector3<DataType> aThirdPoint);
	void InitWithPointAndNormal(Vector3<DataType> aPoint,Vector3<DataType> aNormal);
	bool Inside(Vector3<DataType> aPoint) const;
	union
	{
		struct  
		{
			Vector3<DataType> p1;
		};
			struct  
		{
			Vector3<DataType> myPoint;
		};
	};

	union
	{
		struct  
		{
			Vector3<DataType> p2;
		};
		struct  
		{
			Vector3<DataType> myNormal;
		};
		struct  
		{
			Vector3<DataType> normal;
		};
	};
	
};
template <typename DataType> 
Plane<DataType>::Plane(void)
:	myPoint(0,0,0)
,	myNormal(0,0,0)
{

}
template <typename DataType> 
Plane<DataType>::Plane(Vector3<DataType> aFirstPoint, Vector3<DataType> aSecondPoint,Vector3<DataType> aThirdPoint)
:	myPoint((aFirstPoint+aSecondPoint+aThirdPoint)/3)
,	myNormal((aSecondPoint-aFirstPoint).Cross(aThirdPoint-aSecondPoint).GetNormalize())
{
}
template <typename DataType> 
Plane<DataType>::Plane(const Vector3<DataType>& aPoint,const Vector3<DataType>& aNormal)
:	myPoint(aPoint)
,	myNormal(aNormal)
{
}
template <typename DataType> 
void Plane<DataType>::InitWith3Points(Vector3<DataType> aFirstPoint,Vector3<DataType> aSecondPoint,Vector3<DataType> aThirdPoint)
{
	myPoint = (aFirstPoint+aSecondPoint+aThirdPoint)/3;
	myNormal = (aSecondPoint-aFirstPoint).Cross(aThirdPoint-aSecondPoint).GetNormalize();
}
template <typename DataType> 
void Plane<DataType>::InitWithPointAndNormal(Vector3<DataType> aPoint,Vector3<DataType> aNormal)
{
	myPoint = aPoint;
	myNormal = aNormal;
}
template <typename DataType> 
bool Plane<DataType>::Inside(Vector3<DataType> aPoint) const
{
	if(myNormal.Dot(myPoint - aPoint) >= 0)
	{
		return true;
	}
	return false;
}

#endif