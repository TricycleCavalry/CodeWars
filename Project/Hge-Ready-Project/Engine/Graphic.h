#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

#include "Renderer.h"

#include "Rect.h"


enum GraphicTypes
{
	GT_NULL = -1,
	GT_SPRITE,
	GT_STATIC_ANIMATION,
	GT_DYNAMIC_ANIMATION,
	GT_DISTORTION_MESH,
	GT_FONT,
};

enum BlendModes
{
	BM_COLORADD		=	1,
	BM_COLORMUL		=	0,
	BM_ALPHABLEND	= 	2,
	BM_ALPHAADD		=	0,
	BM_ZWRITE		= 	4,
	BM_NOZWRITE		= 	0,
	BM_DEFAULT		=	2,
};

enum OriginCorners
{
	TOP_LEFT,
	TOP_RIGHT,
	DOWN_LEFT,
	DOWN_RIGHT,
	CENTER_LEFT,
	CENTER_RIGHT,
	CENTER_TOP,
	CENTER_DOWN,
};


class Graphic
{
public:
	Graphic(void);
	virtual~Graphic(void);

	virtual void Init();
	virtual void Update(const float& someElapsedTime);
	virtual void Render(const Vector2<float>& aPosition,const float aLayer = 1.0f,const float aRotation = 0, const float aXScale = 1, const float aYScale = 1, const float& aBaseHeight = 0, const float& aTopHeight = 100 , const WallSides& aSide = W_ROOF, const float& aWidth = 0, const float& aHeight = 0,const DWORD& aColor = WHITE,bool aIsUIFlag = false)=0;

	virtual float GetWidth() = 0;
	virtual float GetHeight() = 0;

	virtual Vector2<float> GetOrigin();
	virtual void SetOriginCorner(const OriginCorners& aOrginCorner);

	virtual void SetBlendMode(const int& aBlendMode);

	virtual Graphic* GetGraphicInstance() = 0;

	virtual int GetActiveFrame();
};

#endif