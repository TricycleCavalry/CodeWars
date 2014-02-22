#include "StdAfx.h"
#include "SpriteWrapper.h"

SpriteWrapper::SpriteWrapper(void)
:	mySprite(NULL)
,	myColor(ARGB(255,255,255,255))
,	myHotSpot(Vector2f(0,0))
,	myBlendMode(BLEND_ALPHABLEND)
,	myZ(0.f)
{
}
SpriteWrapper::SpriteWrapper(hgeSprite *aSprite)
:	mySprite(aSprite)
,	myColor(ARGB(255,255,255,255))
,	myHotSpot(Vector2f(0,0))
,	myBlendMode(BLEND_ALPHABLEND)
,	myZ(0.f)
{
}

SpriteWrapper::SpriteWrapper(const SpriteWrapper& aSpriteWrapper)
:	mySprite(aSpriteWrapper.mySprite)
,	myColor(aSpriteWrapper.myColor)
,	myHotSpot(aSpriteWrapper.myHotSpot)
,	myBlendMode(aSpriteWrapper.myBlendMode)
,	myZ(aSpriteWrapper.myZ)
{
}

SpriteWrapper::~SpriteWrapper(void)
{
}
void SpriteWrapper::SetSprite(hgeSprite *aHgeSprite)
{
	mySprite = aHgeSprite;
}
void SpriteWrapper::Render(Vector2<int> aPosition)
{
	if(mySprite!=NULL)
	{
		PreRender();
		mySprite->Render(static_cast<float>(aPosition.myX), static_cast<float>(aPosition.myY));
	}
}
void SpriteWrapper::Render(Vector2<float> aPosition)
{
	PreRender();
	mySprite->Render(aPosition.myX, aPosition.myY);
}
void SpriteWrapper::Render(Vector2<float> aPosition, const float aRotation)
{
	PreRender();
	mySprite->RenderEx(aPosition.myX, aPosition.myY, aRotation);
}
void SpriteWrapper::Render(Vector2<float> aPosition, const float aRotation, const float anXScale, const float anYScale)
{
	PreRender();
	mySprite->RenderEx(aPosition.myX, aPosition.myY, aRotation, anXScale, anYScale);
}
void SpriteWrapper::SetColor(DWORD aColor)
{
	myColor = aColor;
}
void SpriteWrapper::SetHotSpot(Vector2<float> aHotSpotPosition)
{
	myHotSpot = aHotSpotPosition;
}
void SpriteWrapper::SetBlendMode(const int aBlendMode)
{
	myBlendMode = aBlendMode;
}
void SpriteWrapper::SetZ(const float& aZ)
{
	myZ = aZ;
}
float SpriteWrapper::GetZ()
{
	return myZ;
}
int SpriteWrapper::GetBlendMode()
{
	return myBlendMode;
}
DWORD SpriteWrapper::GetColor()
{
	return myColor;
}
float SpriteWrapper::GetWidth()
{
	return mySprite->GetWidth();
}
float SpriteWrapper::GetHeight()
{
	return mySprite->GetHeight();
}

void SpriteWrapper::PreRender()
{
	mySprite->SetColor(myColor);
	mySprite->SetHotSpot(myHotSpot.myX, myHotSpot.myY);
	mySprite->SetBlendMode(myBlendMode);
	mySprite->SetZ(myZ);
}