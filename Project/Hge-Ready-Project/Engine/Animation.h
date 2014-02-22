#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include "graphic.h"

#include "GrowingArray.h"

class Sprite;

class Animation : public Graphic
{
public:
	Animation(GrowingArray<Sprite*> someSprites,const float& anInterval, const bool& aLoopFlag);
	Animation(const Animation& anAnimation);
	~Animation(void);

	void Update(const float& someElapsedTime);
	void Render(const Vector2<float>& aPosition,const float aLayer = 1.0f,const float aRotation = 0, const float aXScale = 1, const float aYScale = 1, const float& aBaseHeight = 0, const float& aTopHeight = 100, const WallSides& aSide = W_ROOF, const float& aWidth = 0, const float& aHeight = 0, const DWORD& aColor = WHITE,bool aIsUIFlag = false);

	float GetWidth();
	float GetHeight();

	void SetOriginCorner(const OriginCorners& aOrginCorner);

	void SetBlendMode(const int& aBlendMode);

	Graphic* GetGraphicInstance();

	 int GetActiveFrame();

	
private:
	GrowingArray<Sprite*> mySprites;
	int	myCurrentSprite;

	float	myInterval;
	float	myIntervalCounter;
	bool	myLoopFlag;

	
};

#endif