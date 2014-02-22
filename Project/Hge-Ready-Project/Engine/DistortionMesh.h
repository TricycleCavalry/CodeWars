#ifndef _DISTORTION_MESH_HEADER_
#define _DISTORTION_MESH_HEADER_

#include "graphic.h"

class DistortionMesh : public Graphic
{
public:
	DistortionMesh(Renderer& aRenderer);
	DistortionMesh(const DistortionMesh& aMesh);
	~DistortionMesh(void);

	DistortionMesh& operator=(const DistortionMesh& aMesh);

	void Init(const int& aID,const int aBlendMode,const Rect& aSpriteSheetRect);

	void Render(const Vector2<float>& aPosition,const float aLayer = 1.0f,const float aRotation = 0, const float aXScale = 1, const float aYScale = 1, const float& aBaseHeight = 0, const float& aTopHeight = 100, const WallSides& aSide = W_ROOF, const float& aWidth = 0, const float& aHeight = 0, const DWORD& aColor = WHITE,bool aIsUIFlag = false);

	Graphic* GetGraphicInstance();

	float GetWidth();
	float GetHeight();

	int myID;
	int myBlendMode;
	Rect mySpriteSheetRect;

private:
	Renderer& myRenderer;
};

#endif