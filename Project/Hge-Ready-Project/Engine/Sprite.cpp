#pragma warning (disable:4005)
#include "Sprite.h"

Sprite::Sprite(Renderer& aRenderer)
:	myRenderer(aRenderer)
,	myRotation(0.0f)
{
}

Sprite::Sprite(const Sprite& aSprite)
:	myRenderer(aSprite.myRenderer)
,	myID(aSprite.myID)
,	myBlendMode(aSprite.myBlendMode)
,	mySpriteSheetRect(aSprite.mySpriteSheetRect)
,	myOrgin(aSprite.myOrgin)
,	myRotation(aSprite.myRotation)
{
}

Sprite::~Sprite(void)
{
}

Sprite& Sprite::operator=(const Sprite& aSprite)
{
	myID = aSprite.myID;
	myBlendMode = aSprite.myBlendMode;
	mySpriteSheetRect = aSprite.mySpriteSheetRect;
	myOrgin = aSprite.myOrgin;
	myRotation = aSprite.myRotation;

	return *this;
}

void Sprite::Init(const int& aID,const int aBlendMode,const Rect& aSpriteSheetRect,const Vector2<float> aOrgin, const float& aRotation)
{
	myID				= aID;
	myBlendMode			= aBlendMode;
	mySpriteSheetRect	= aSpriteSheetRect;
	myOrgin				= aOrgin;
	myRotation			= aRotation;
}
void Sprite::Render(const Vector2<float>& aPosition,const float aLayer,const float aRotation, const float aXScale, const float aYScale,const float& aBaseHeight, const float& aTopHeight, const WallSides& aSide, const float& aWidth, const float& aHeight, const DWORD& aColor,bool aIsUIFlag)
{
	myRenderer.AddToRenderQueue(*this,aPosition.myX,aPosition.myY,aLayer,(myRotation+aRotation),aXScale,aYScale,aColor,aIsUIFlag);
}

Graphic* Sprite::GetGraphicInstance()
{
	return new Sprite(*this);
	
}
float Sprite::GetWidth()
{
	return mySpriteSheetRect.myWidth;
}
float Sprite::GetHeight()
{
	return mySpriteSheetRect.myHeight;
}

Vector2<float> Sprite::GetOrigin()
{
	return myOrgin;
}
void Sprite::SetOriginCorner(const OriginCorners& aOrginCorner)
{
	switch(aOrginCorner)
	{
	case TOP_LEFT:
		myOrgin = Vector2<float>(0.f,0.f);
		break;
	case TOP_RIGHT:
		myOrgin = Vector2<float>(mySpriteSheetRect.myWidth,0.f);
		break;
	case DOWN_LEFT:
		myOrgin = Vector2<float>(0.f,mySpriteSheetRect.myHeight);
		break;
	case DOWN_RIGHT:
		myOrgin = Vector2<float>(mySpriteSheetRect.myWidth,mySpriteSheetRect.myHeight);
		break;
	case CENTER_LEFT:
		myOrgin = Vector2<float>(0.f,mySpriteSheetRect.myHeight/2.f);
		break;
	case CENTER_RIGHT:
		myOrgin = Vector2<float>(mySpriteSheetRect.myWidth,mySpriteSheetRect.myHeight/2.f);
		break;
	case CENTER_TOP:
		myOrgin = Vector2<float>(mySpriteSheetRect.myWidth/2,0.f);
		break;
	case CENTER_DOWN:
		myOrgin = Vector2<float>(mySpriteSheetRect.myWidth/2,mySpriteSheetRect.myHeight);
		break;
	}
}

void Sprite::SetBlendMode(const int& aBlendMode)
{
	myBlendMode = aBlendMode;
}