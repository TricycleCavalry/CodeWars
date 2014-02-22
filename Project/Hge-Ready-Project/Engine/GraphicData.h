#ifndef _GRAPHIC_DATA_H_
#define _GRAPHIC_DATA_H_

#include "Vector2.h"
class Graphic;

struct GraphicData
{
	GraphicData()
		:	myIsDecal(false)
		,	myTimer(0.f)
	{
	}
	Vector2<float>	myPosition;
	float			myLayer;
	float			myRotation;
	Graphic*		myGraphic;
	bool			myIsDecal;
	float			myTimer;
};

#endif