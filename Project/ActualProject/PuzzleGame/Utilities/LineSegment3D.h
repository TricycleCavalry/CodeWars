#ifndef LINE_SEGMENT_3D
#define LINE_SEGMENT_3D


#define _USE_MATH_DEFINES
#include <cmath>
#include "Vector3.h"


template<typename DataType = float> class LineSegment3
{
public:
	LineSegment3(void);
	LineSegment3(Vector3<DataType> aFirstPoint,Vector3<DataType> aSecondPoint);
	~LineSegment3(void);

	void InitWith2Points(Vector3<DataType> aFirstPoint, Vector3<DataType> aSecondPoint);
	void InitWithPointAndDirection(Vector3<DataType> aPoint, Vector3<DataType> aDirection);

	DataType Length() const;

	Vector3<DataType> GetDirection() const;

	



	union
	{
		struct
		{
			Vector3<DataType> p1;
		};
		struct
		{
			Vector3<DataType> myFirstPoint;		
		};
		struct
		{
			Vector3<DataType> myStartPos;
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
			Vector3<DataType> mySecondPoint;
		};
		struct
		{
			Vector3<DataType> myEndPos;
		};
	};

};

template<typename DataType>
LineSegment3<DataType>::LineSegment3(void)
	:	p1(0,0,0)
	,	p2(0,0,0)
{
}
template<typename DataType>
LineSegment3<DataType>::LineSegment3(Vector3<DataType> aFirstPoint,Vector3<DataType> aSecondPoint)
	:	p1(aFirstPoint)
	,	p2(aSecondPoint)
{
}
template<typename DataType>
LineSegment3<DataType>::~LineSegment3(void)
{
}
template<typename DataType>
void LineSegment3<DataType>::InitWith2Points(Vector3<DataType> aFirstPoint, Vector3<DataType> aSecondPoint)
{
	p1 = aFirstPoint;
	p2 = aSecondPoint;
}
template<typename DataType>
void LineSegment3<DataType>::InitWithPointAndDirection(Vector3<DataType> aPoint, Vector3<DataType> aDirection)
{
	p1 = aPoint;
	p2 = aDirection;
}
template<typename DataType>
DataType LineSegment3<DataType>::Length() const
{
	return (p2-p1).Length();
}
template<typename DataType>
Vector3<DataType> LineSegment3<DataType>::GetDirection() const
{
	return Vector3<DataType>(p2-p1).GetNormalize();
}



#endif