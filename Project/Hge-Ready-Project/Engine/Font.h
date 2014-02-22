#ifndef _FONT_H_
#define _FONT_H_

#include "Vector2.h"
class Renderer;
typedef unsigned long       DWORD;
#include "Graphic.h"


#include <string>

class Font
{
public:
	Font(Renderer& aRenderer);
	Font(const Font& aFont);
	~Font(void);

	void Init(const int& aId,const DWORD& aColor);
	void Update(const float& someElapsedTime);

	void Render(const Vector2<float>& aPosition, const float& aLayer,const float& aRotation,const float& aScale, const int& anAlignment,const std::string& aText,const float& aBoxWidth = 2048.f,const float& aBoxHeight = 2048.f);

	Font* GetInstance();
	
	void SetOriginCorner(const OriginCorners& aOrginCorner);

	int myId;
	DWORD myColor;
	Vector2<float> myOrgin;
private:

	Renderer& myRenderer;
};

#endif