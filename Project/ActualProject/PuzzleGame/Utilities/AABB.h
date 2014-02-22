#ifndef AABB_HEADER
#define AABB_HEADER

#include "GrowingArray.h"
#include "Vector3.h"

namespace Intersection
{
	class AABB
	{
	public:
		AABB(void);
		AABB(const Vector3<float>& aMinPos,const Vector3<float>& aMaxPos);
		~AABB(void);

		void Init(const GrowingArray<Vector3f>& someCorners);

		Vector3<float> myCenterPos;
		Vector3<float> myExtents;
		Vector3<float> myMinPos;
		Vector3<float> myMaxPos;
	};
};
using namespace Intersection;
#endif