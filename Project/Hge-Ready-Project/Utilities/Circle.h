#ifndef _CIRCLE_HEADER_
#define _CIRCLE_HEADER_

#include "Vector2.h"

class Circle
{
public:
	Circle(const Vector2<float>& aCenterPosition, const float& aRadius);
	~Circle(void);

	union
	{
		struct
		{
			Vector2<float> myCenterPosition;
		};
		struct
		{
			union
			{
				float x;
				float myX;
			};

			union
			{
				float y;
				float myY;
			};
		};

	};

	union
	{
		float myRadius;
		float r;
	};
};

#endif