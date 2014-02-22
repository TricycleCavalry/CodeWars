#pragma warning (disable:4005)
#include "Animation.h"
#include "Sprite.h"

Animation::Animation(GrowingArray<Sprite*> someSprites,const float& anInterval, const bool& aLoopFlag)
:	mySprites(someSprites)
,	myCurrentSprite(0)
,	myInterval(anInterval)
,	myIntervalCounter(0)
,	myLoopFlag(aLoopFlag)
{
}
Animation::Animation(const Animation& anAnimation)
:	mySprites(2)
,	myInterval(anAnimation.myInterval)
,	myIntervalCounter(anAnimation.myIntervalCounter)
,	myLoopFlag(anAnimation.myLoopFlag)
,	myCurrentSprite(0)
{
	for(int i = 0; i < anAnimation.mySprites.Count(); ++i)
	{
		mySprites.Add(reinterpret_cast<Sprite*>(anAnimation.mySprites[i]->GetGraphicInstance()));
	}
}
Animation::~Animation(void)
{
	mySprites.DeleteAll();
}
void Animation::Update(const float& someElapsedTime)
{
	if(someElapsedTime < 0)
	{
		myCurrentSprite = 0;
		myIntervalCounter  = 0;
		return;
	}
	if(myCurrentSprite == mySprites.Count()-1 && myLoopFlag == false)
	{
		return;
	}

	myIntervalCounter += someElapsedTime;

	if(myIntervalCounter >= myInterval)
	{
		++myCurrentSprite;
		myIntervalCounter = 0;
	}

	if(myCurrentSprite > mySprites.Count()-1)
	{
		if(myLoopFlag == false)
		{			
			myCurrentSprite = mySprites.Count()-1;
			return;
		}
		myCurrentSprite = 0;
	}
}
void Animation::Render(const Vector2<float>& aPosition,const float aLayer,const float aRotation, const float aXScale, const float aYScale,const float& aBaseHeight, const float& aTopHeight, const WallSides& aSide, const float& aWidth, const float& aHeight, const DWORD& aColor,bool aIsUIFlag)
{
	mySprites[myCurrentSprite]->Render(aPosition,aLayer,aRotation,aXScale,aYScale,0,0,W_ROOF,0,0,aColor,aIsUIFlag);
}
float Animation::GetWidth()
{
	if(myCurrentSprite < mySprites.Count())
	{
		return mySprites[myCurrentSprite]->GetWidth();
	}
	return 0.f;
}
float Animation::GetHeight()
{
	if(myCurrentSprite < mySprites.Count())
	{
		return mySprites[myCurrentSprite]->GetHeight();
	}
	return 0.f;
}
void Animation::SetOriginCorner(const OriginCorners& aOrginCorner)
{
	for(int i = 0; i < mySprites.Count(); ++i)
	{
		mySprites[i]->SetOriginCorner(aOrginCorner);
	}
}

void Animation::SetBlendMode(const int& aBlendMode)
{
	for(int i=0;i<mySprites.Count();i++)
	{
		mySprites[i]->SetBlendMode(aBlendMode);
	}
}

Graphic* Animation::GetGraphicInstance()
{
	return new Animation(*this);
}

int Animation::GetActiveFrame()
{
	return myCurrentSprite;
}