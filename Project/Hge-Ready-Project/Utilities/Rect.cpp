#include "Rect.h"
Rect::Rect(void)
:myPosition(0.f,0.f)
,myWidth(0.f)
,myHeight(0.f)
{
}
Rect::Rect(const Vector2<float>& aPosition, const float& aWidth, const float& aHeight)
:myPosition(aPosition)
,myWidth(aWidth)
,myHeight(aHeight)
{
}

Rect::~Rect(void)
{
}

bool Rect::IsInside(const float& aX,const float& aY)
{
	if(aX < myPosition.myX + myWidth 
		&& aX > myPosition.myX 
		&& aY < myPosition.myY + myHeight
		&& aY > myPosition.myY)
	{
		return true;
	}
	return false;
}
