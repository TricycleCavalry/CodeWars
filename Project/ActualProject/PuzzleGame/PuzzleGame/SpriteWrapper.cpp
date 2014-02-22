#include "StdAfx.h"
#include "SpriteWrapper.h"

SpriteWrapper::SpriteWrapper(void)
:mySprite(NULL)
{
}
SpriteWrapper::SpriteWrapper(hgeSprite *aSprite)
:mySprite(aSprite)
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
		mySprite->Render(static_cast<float>(aPosition.myX), static_cast<float>(aPosition.myY));
}
void SpriteWrapper::Render(Vector2<float> aPosition)
{
	mySprite->Render(aPosition.myX, aPosition.myY);
}
void SpriteWrapper::Render(Vector2<float> aPosition, const float aRotation)
{
	mySprite->RenderEx(aPosition.myX, aPosition.myY, aRotation);
}
void SpriteWrapper::Render(Vector2<float> aPosition, const float aRotation, const float anXScale, const float anYScale)
{
	mySprite->RenderEx(aPosition.myX, aPosition.myY, aRotation, anXScale, anYScale);
}
void SpriteWrapper::SetColor(DWORD aColor)
{
	mySprite->SetColor(aColor);
}
void SpriteWrapper::SetHotSpot(Vector2<float> aHotSpotPosition)
{
	mySprite->SetHotSpot(aHotSpotPosition.myX, aHotSpotPosition.myY);
}
void SpriteWrapper::SetBlendMode(const int aBlendMode)
{
	mySprite->SetBlendMode(aBlendMode);
}
int SpriteWrapper::GetBlendMode()
{
	return mySprite->GetBlendMode();
}
DWORD SpriteWrapper::GetColor()
{
	return mySprite->GetColor();
}
float SpriteWrapper::GetWidth()
{
	return mySprite->GetWidth();
}
float SpriteWrapper::GetHeight()
{
	return mySprite->GetHeight();
}