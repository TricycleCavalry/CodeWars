#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Graphic.h"


class Sprite : public Graphic
{
public:
	Sprite(Renderer& aRenderer);
	Sprite(const Sprite& aSprite);
	~Sprite(void);

	Sprite& operator=(const Sprite& aSprite);

	void Init(const int& aID,const int aBlendMode,const Rect& aSpriteSheetRect,const Vector2<float> aOrgin, const float& aRotation);

	void Render(const Vector2<float>& aPosition,const float aLayer = 1.0f,const float aRotation = 0, const float aXScale = 1, const float aYScale = 1, const float& aBaseHeight = 0, const float& aTopHeight = 100, const WallSides& aSide = W_ROOF, const float& aWidth = 0, const float& aHeight = 0, const DWORD& aColor = WHITE,bool aIsUIFlag = false);

	Graphic* GetGraphicInstance();

	float GetWidth();
	float GetHeight();

	Vector2<float> GetOrigin();
	void SetOriginCorner(const OriginCorners& aOrginCorner);

	void SetBlendMode(const int& aBlendMode);

	int myID;
	int myBlendMode;
	Rect mySpriteSheetRect;
	Vector2<float> myOrgin;
	float myRotation;
private:	
	Renderer& myRenderer;

};

#endif