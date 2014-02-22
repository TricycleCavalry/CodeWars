#ifndef _SPRITE_WRAPPER_H_
#define _SPRITE_WRAPPER_H_

#include "hgeSprite.h"
#include "StringId.h"
#include "Vector.h"

class SpriteWrapper
{
public:
	SpriteWrapper(void);
	SpriteWrapper(hgeSprite *aSprite);
	~SpriteWrapper(void);

	void SetSprite(hgeSprite *aHgeSprite);

	void Render(Vector2<float> aPosition);
	void Render(Vector2<float> aPosition, const float aRotation);
	void Render(Vector2<float> aPosition, const float aRotation, const float anXScale, const float anYScale);

	void SetColor(DWORD aColor);
	void SetHotSpot(Vector2<float> aHotSpotPosition);
	void SetBlendMode(const int aBlendMode);

	int GetBlendMode();
	DWORD GetColor();
	float GetWidth();
	float GetHeight();

private:
	hgeSprite *mySprite;
};

#endif