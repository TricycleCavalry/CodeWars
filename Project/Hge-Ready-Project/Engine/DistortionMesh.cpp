#pragma warning (disable:4005)
#include "DistortionMesh.h"

DistortionMesh::DistortionMesh(Renderer& aRenderer)
:	myRenderer(aRenderer)
{
}

DistortionMesh::DistortionMesh(const DistortionMesh& aMesh)
:	myRenderer(aMesh.myRenderer)
{
	*this = aMesh;
}

DistortionMesh::~DistortionMesh(void)
{
}

DistortionMesh& DistortionMesh::operator=(const DistortionMesh& aMesh)
{
	myID				= aMesh.myID;
	myBlendMode			= aMesh.myBlendMode;
	mySpriteSheetRect	= aMesh.mySpriteSheetRect;

	return *this;
}

void DistortionMesh::Init(const int& aID,const int aBlendMode,const Rect& aSpriteSheetRect)
{
	myID				= aID;
	myBlendMode			= aBlendMode;
	mySpriteSheetRect	= aSpriteSheetRect;
}

void DistortionMesh::Render(const Vector2<float> &aPosition, const float aLayer,const float aRotation, const float aXScale, const float aYScale,const float& aBaseHeight, const float& aTopHeight, const WallSides& aSide, const float& aWidth, const float& aHeight, const DWORD& aColor,bool aIsUIFlag)
{
	myRenderer.AddToRenderQueue(*this,aPosition.x,aPosition.y,aLayer,aBaseHeight,aTopHeight,aSide,aWidth,aHeight,aColor,aIsUIFlag);
}

Graphic* DistortionMesh::GetGraphicInstance()
{
	return new DistortionMesh(*this);
}

float DistortionMesh::GetWidth()
{
	return mySpriteSheetRect.myWidth;
}

float DistortionMesh::GetHeight()
{
	return mySpriteSheetRect.myHeight;
}