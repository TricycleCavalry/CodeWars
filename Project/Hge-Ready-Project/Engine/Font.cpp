#pragma warning (disable:4005)
#include "Font.h"
#include "DEBUG.h"
#include "Renderer.h"
#include "hgeFont.h"



#define NULL 0

Font::Font(Renderer& aRenderer)
:	myRenderer(aRenderer)
,	myOrgin(0.f,0.f)
{
}
Font::Font(const Font& aFont)
:	myRenderer(aFont.myRenderer)
,	myId(aFont.myId)
,	myColor(aFont.myColor)
,	myOrgin(aFont.myOrgin)
{
}
Font::~Font(void)
{
}

void Font::Init(const int& aId,const DWORD& aColor)
{
	myId = aId;
	myColor = aColor;
}
void Font::Update(const float& someElapsedTime)
{
}
void Font::Render(const Vector2<float>& aPosition, const float& aLayer,const float& aRotation,const float& aScale, const int& anAlignment,const std::string& aText,const float& aBoxWidth,const float& aBoxHeight)
{
	myRenderer.AddToRenderQueue(*this,aPosition.x,aPosition.y,aLayer,aRotation,aScale,myColor,anAlignment,aText,aBoxWidth,aBoxHeight);
}

Font* Font::GetInstance()
{
	return new Font(*this);
}





