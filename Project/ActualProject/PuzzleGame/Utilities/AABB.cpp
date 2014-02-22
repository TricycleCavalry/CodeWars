#include "StdAfx.h"
#include "AABB.h"

using namespace Intersection;

AABB::AABB(void)
{
}
AABB::AABB(const Vector3<float>& aMinPos,const Vector3<float>& aMaxPos)
	:	myMinPos(aMinPos)
	,	myMaxPos(aMaxPos)
	,	myExtents(aMaxPos - aMinPos)	
{
	myCenterPos = aMaxPos -  Vector3<float>(abs(aMinPos.x),abs(aMinPos.y),abs(aMinPos.z));
}
AABB::~AABB(void)
{
}

void AABB::Init(const GrowingArray<Vector3<float>>& someCorners)
{
	myMinPos = Vector3<float>(SHRT_MAX,SHRT_MAX,SHRT_MAX);
	myMaxPos = Vector3<float>(SHRT_MIN,SHRT_MIN,SHRT_MIN);
	for(int i=0;i<someCorners.Count();i++)
	{
		if(myMinPos.x > someCorners[i].x)
		{
			myMinPos.x = someCorners[i].x;
		}
		if(myMaxPos.x < someCorners[i].x)
		{
			myMaxPos.x = someCorners[i].x;
		}

		if(myMinPos.y > someCorners[i].y)
		{
			myMinPos.y = someCorners[i].y;
		}
		if(myMaxPos.y < someCorners[i].y)
		{
			myMaxPos.y = someCorners[i].y;
		}

		if(myMinPos.z > someCorners[i].z)
		{
			myMinPos.z = someCorners[i].z;
		}
		if(myMaxPos.z < someCorners[i].z)
		{
			myMaxPos.z = someCorners[i].z;
		}
	}

	myExtents = myMaxPos - myMinPos;
	myCenterPos = myMinPos + (myExtents/2);
}