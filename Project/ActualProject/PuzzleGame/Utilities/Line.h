#ifndef LINE_HEADER
#define LINE_HEADER

#pragma warning ( disable: 4005)
#include "Vector2.h"

#define _USE_MATH_DEFINES
#include <cmath>


template<typename DataType> class Line
{
public:
	Line(void);
	Line(Vector2<DataType> aFirstPoint,Vector2<DataType> aSecondPoint);
	Line(const Line<DataType>& aLine);
	~Line(void);

	void InitWith2Points(Vector2<DataType> aFirstPoint, Vector2<DataType> aSecondPoint);
	void InitWithPointAndDirection(Vector2<DataType> aPoint, Vector2<DataType> aDirection);
	
	const bool Inside(Vector2<DataType> aPoint) const;
	union
	{
		struct
		{
			Vector2<DataType> myPoints[2];
		};
		struct
		{
			Vector2<DataType> p1;
			Vector2<DataType> p2;
		};
	};

};

template<typename DataType>
Line<DataType>::Line(void)
:	p1(0,0)
,	p2(0,0)
{
}
template<typename DataType>
Line<DataType>::Line(Vector2<DataType> aFirstPoint,Vector2<DataType> aSecondPoint)
:	p1(aFirstPoint)
,	p2(aSecondPoint)
{
}
template<typename DataType>
Line<DataType>::Line(const Line<DataType>& aLine)
:	p1(aLine.p1)
,	p2(aLine.p2)
{
}
template<typename DataType>
Line<DataType>::~Line(void)
{
}
template<typename DataType>
void Line<DataType>::InitWith2Points(Vector2<DataType> aFirstPoint, Vector2<DataType> aSecondPoint)
{
	p1 = aFirstPoint;
	p2 = aSecondPoint;
}
template<typename DataType>
void Line<DataType>::InitWithPointAndDirection(Vector2<DataType> aPoint, Vector2<DataType> aDirection)
{
	p1 = aPoint;
	p2 = aDirection;
}
template<typename DataType>
const bool Line<DataType>::Inside(Vector2<DataType> aPoint) const
{
	Vector2<DataType> normal = (p1-p2).GetNormalize();
	normal.Rotate(static_cast<DataType>(90));
	DataType distance0 = normal.Dot(p2);
	DataType distance1 = normal.Dot(aPoint);
	if(distance1-distance0 > 0)
	{
		return true;
	}
	return false;
	
}
#endif