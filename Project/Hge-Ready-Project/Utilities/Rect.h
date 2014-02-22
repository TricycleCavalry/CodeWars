#ifndef _RECT_HEADER_
#define _RECT_HEADER_

#include "Vector2.h"



class Rect
{
public:
	Rect(void);
	Rect(const Vector2<float>& aPosition, const float& aWidth, const float& aHeight);
	~Rect(void);

	bool IsInside(const float& aX,const float& aY);

	Vector2<float> myPosition;

	float myWidth;
	float myHeight;
};

#endif