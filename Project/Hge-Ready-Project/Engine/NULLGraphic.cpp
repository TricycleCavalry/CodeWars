#pragma warning (disable:4005)
#include "NULLGraphic.h"

NULLGraphic::NULLGraphic(void)
:	Graphic()
{
}

NULLGraphic::~NULLGraphic(void)
{
}

void NULLGraphic::Init()
{
}

void NULLGraphic::Update(const float& someElapsedTime)
{
}

void NULLGraphic::Render(const Vector2<float>& aPosition,const float aLayer,const float aRotation, const float aXScale, const float aYScale,const float& aBaseHeight, const float& aTopHeight, const WallSides& aSide, const float& aWidth, const float& aHeight,bool aIsUIFlag)
{
}
float NULLGraphic::GetWidth()
{
	return NULL;
}
float NULLGraphic::GetHeight()
{
	return NULL;
}
Graphic* NULLGraphic::GetGraphicInstance()
{
	return this;
}
