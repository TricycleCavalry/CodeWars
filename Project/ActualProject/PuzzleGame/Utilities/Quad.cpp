#include "Quad.h"

#include "Triangle.h"
#include "Edge.h"

Quad::Quad(void)
{
}

Quad::~Quad(void)
{
}

void Quad::GenerateQuadFromPoints(const Vector3f& aFirstPoint,const Vector3f& aSecondPoint,const Vector3f& aThirdPoint,const Vector3f& aFourthPoint)
{
	myPoints[0] = aFirstPoint;
	myPoints[1] = aSecondPoint;
	myPoints[2] = aThirdPoint;
	myPoints[3] = aFourthPoint;
}