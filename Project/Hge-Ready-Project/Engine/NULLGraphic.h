#ifndef _NULL_GRAPHIC_H_
#define _NULL_GRAPHIC_H_
#include "graphic.h"

class NULLGraphic :	public Graphic
{
public:
	NULLGraphic(void);
	~NULLGraphic(void);
	void Init();
	void Update(const float& someElapsedTime);
	void Render(const Vector2<float>& aPosition,const float aLayer = 1.0f,const float aRotation = 0, const float aXScale = 1, const float aYScale = 1, const float& aBaseHeight = 0, const float& aTopHeight = 100, const WallSides& aSide = W_ROOF, const float& aWidth = 0, const float& aHeight = 0,bool aIsUIFlag = false);


	float GetWidth();
	float GetHeight();

	Graphic* GetGraphicInstance();
};

#endif