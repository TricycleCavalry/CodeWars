#ifndef _BASE_FACTORY_HEADER_
#define _BASE_FACTORY_HEADER_

#include "GrowingArray.h"
#include "Vector2.h"
#include "Rect.h"
//#include <string>
#include "Graphic.h"


class CollisionSystem;

class BaseFactory
{
public:
	BaseFactory(void);
	virtual ~BaseFactory(void);
protected:

	Rect			GetRectangle(const char* aRectangle);
	Vector2<float>	GetVector(const char* aVector);
	float			GetFloat(const char* aFloat);
	int				GetInt(const char* anInt);
	bool			GetBool(const char* aBool);
	DWORD			GetColor(const char* aColor);

	int				FindElement(const GrowingArray<std::string>& anArray, const std::string& anIdToFind);


	OriginCorners GetCorner(std::string aString);
	Vector2<float> GetPositionDependentOnCorner(const OriginCorners& aCorner,const Vector2<float>& aPosition,const Vector2<int>& someWindowDimensions);
};

#endif