#pragma warning (disable:4005)
#include "Graphic.h"
#include "Debug.h"
#include "Sprite.h"


Graphic::Graphic(void)
{
}
Graphic::~Graphic(void)
{
}

void Graphic::Init()
{
	DL_ASSERT("Wrong Init function was called! Contact Programmers");
}
void Graphic::Update(const float& someElapsedTime)
{
	//DL_ASSERT("Wrong Update function was called! Contact Programmers");
}

Vector2<float> Graphic::GetOrigin()
{
	return Vector2<float>(0,0);
}
void Graphic::SetOriginCorner(const OriginCorners& aOrginCorner)
{
	return;
}

void Graphic::SetBlendMode(const int& aBlendMode)
{
	return;
}

int Graphic::GetActiveFrame()
{
	return 0;
}