#ifndef QUAD_HEADER
#define QUAD_HEADER

#include "Vector3.h"

class Quad
{
public:
	Quad(void);
	~Quad(void);

	void GenerateQuadFromPoints(const Vector3f& aFirstPoint,const Vector3f& aSecondPoint,const Vector3f& aThirdPoint,const Vector3f& aFourthPoint);

	Vector3f myPoints[4];
	Vector3f myNormal;
};

#endif