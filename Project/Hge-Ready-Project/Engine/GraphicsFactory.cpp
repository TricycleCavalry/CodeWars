#include "GraphicsFactory.h"
#include "TimeManager.h"

#include "Graphic.h"
#include "Sprite.h"
#include "Animation.h"
#include "DistortionMesh.h"
#include "Font.h"



GraphicsFactory::GraphicsFactory(void)
:	myRenderer(NULL)
,	myTimeManager(NULL)
{
}

GraphicsFactory::~GraphicsFactory(void)
{
}

void GraphicsFactory::Init(Renderer* aRenderer,TimeManager* aTimeManager)
{
	myGraphics.Init(8);
	myGraphicsIds.Init(8,true);
	myFonts.Init(8);
	myFontIds.Init(8,true);
	myRenderer = aRenderer;
	myTimeManager = aTimeManager;
}
void GraphicsFactory::LoadSpriteSheets(tinyxml2::XMLDocument* aXMLDocument)
{
	tinyxml2::XMLElement* xmlElement = aXMLDocument->FirstChildElement();

	do
	{
		if(GetBool(xmlElement->Attribute("IsMesh")) == true)
		{
			myRenderer->AddMeshTexture(xmlElement->Attribute("Path"),xmlElement->Attribute("SpriteSheetId"));
		}
		else
		{
			myRenderer->AddTexture(xmlElement->Attribute("Path"),xmlElement->Attribute("SpriteSheetId"));
		}
		xmlElement = xmlElement->NextSiblingElement();
	}while(xmlElement != NULL);
}

void GraphicsFactory::LoadGraphics(tinyxml2::XMLDocument* aXMLDocument)
{
	LoadGraphics(aXMLDocument->FirstChildElement());
}
void GraphicsFactory::LoadGraphics(tinyxml2::XMLElement* aXMLElement)
{
	tinyxml2::XMLElement* graphicElement = aXMLElement;
	do
	{
		LoadGraphic(graphicElement);
		graphicElement = graphicElement->NextSiblingElement();
	}while(graphicElement != NULL);
}
Graphic* GraphicsFactory::GetGraphic(const std::string& aGraphicId)
{
	int i =  FindElement(myGraphicsIds,aGraphicId);
	return myGraphics[i];
}
Font* GraphicsFactory::GetFont(const std::string& aFontId)
{
	int i = FindElement(myFontIds,aFontId);
	return myFonts[i]->GetInstance();
}
void GraphicsFactory::LoadGraphic(tinyxml2::XMLElement* aXMLElement)
{

	tinyxml2::XMLElement* graphicElement = aXMLElement;
	GraphicTypes type = GetGraphicType(graphicElement->Attribute("Type"));

	switch(type)
	{
	case GT_SPRITE:
		LoadSprite(graphicElement);
		break;
	case GT_STATIC_ANIMATION:
		LoadStaticAnimation(graphicElement);
		break;
	case GT_DYNAMIC_ANIMATION:
		break;
	case GT_DISTORTION_MESH:
		LoadDistortionMesh(graphicElement);
		break;
	case GT_FONT:
		LoadFont(graphicElement);
		break;
	}
}

GraphicTypes GraphicsFactory::GetGraphicType(const std::string& aType)
{
	if( "Sprite" == aType)
	{
		return GT_SPRITE;
	}
	if( "StaticAnimation" == aType )
	{
		return GT_STATIC_ANIMATION;
	}
	if( "DynamicAnimation" == aType )
	{
		return GT_DYNAMIC_ANIMATION;
	}
	if( "DistortionMesh" == aType )
	{
		return GT_DISTORTION_MESH;
	}
	if( "Font" == aType )
	{
		return GT_FONT;
	}
	DL_ASSERT("Wrong GraphicType somewhere!");
	return GT_NULL;
}

void GraphicsFactory::LoadSprite(tinyxml2::XMLElement* aXMLElement)
{
	tinyxml2::XMLElement* graphicElement = aXMLElement;

	std::string		spriteSheetId	= graphicElement->Attribute("SpriteSheetId");
	std::string		graphicId		= graphicElement->Attribute("GraphicId");
	Rect			spriteSheetRect	= GetRectangle(graphicElement->Attribute("SpriteSheetRectangle"));
	Vector2<float>	orgin			= GetVector(graphicElement->Attribute("Origin"));
	BlendModes		blendMode		= GetBlendMode(graphicElement->Attribute("BlendMode"));
	float			rotation		= GetFloat(graphicElement->Attribute("Rotation"))*static_cast<float>(M_PI)/180.f;

	myGraphics.Add(myRenderer->AddSprite(spriteSheetId,spriteSheetRect,orgin,blendMode,rotation));
	myGraphicsIds.Add(graphicId);
}
void GraphicsFactory::LoadStaticAnimation(tinyxml2::XMLElement* aXMLElement)
{
	tinyxml2::XMLElement* graphicElement = aXMLElement;

	std::string		spriteSheetId	= graphicElement->Attribute("SpriteSheetId");
	std::string		graphicId		= graphicElement->Attribute("GraphicId");
	Rect			spriteSheetRect	= GetRectangle(graphicElement->Attribute("SpriteSheetRectangle"));
	Vector2<float>	orgin			= GetVector(graphicElement->Attribute("Origin"));
	BlendModes		blendMode		= GetBlendMode(graphicElement->Attribute("BlendMode"));
	float			interval		= GetFloat(graphicElement->Attribute("Interval"));
	int				numOfImages		= GetInt(graphicElement->Attribute("NumberOfImages"));
	bool			loop			= GetBool(graphicElement->Attribute("Loop"));

	GrowingArray<Sprite*> animationSprites(2);
	for(int i = 0; i  < numOfImages; ++i)
	{
		animationSprites.Add(myRenderer->AddSprite(spriteSheetId,spriteSheetRect,orgin,blendMode));
		spriteSheetRect.myPosition.myX += spriteSheetRect.myWidth;
	}
	myGraphicsIds.Add(graphicId);
	myGraphics.Add(new Animation(animationSprites,interval,loop));

}
void GraphicsFactory::LoadDynamicAnimation(tinyxml2::XMLElement* aXMLElement)
{
	tinyxml2::XMLElement* graphicElement = aXMLElement;
}

void GraphicsFactory::LoadDistortionMesh(tinyxml2::XMLElement* aXMLElement)
{
	tinyxml2::XMLElement* graphicElement = aXMLElement;

	std::string		spriteSheetId	= graphicElement->Attribute("SpriteSheetId");
	std::string		graphicId		= graphicElement->Attribute("GraphicId");
	Rect			spriteSheetRect = GetRectangle(graphicElement->Attribute("SpriteSheetRectangle"));
	BlendModes		blendMode		= GetBlendMode(graphicElement->Attribute("BlendMode"));

	myGraphics.Add(myRenderer->AddMesh(spriteSheetId,spriteSheetRect,blendMode));
	myGraphicsIds.Add(graphicId);
}

void GraphicsFactory::LoadFont(tinyxml2::XMLElement* aXMLElement)
{
	tinyxml2::XMLElement* graphicElement = aXMLElement;
	std::string	filePath	= graphicElement->Attribute("FilePath");
	std::string	fontId		= graphicElement->Attribute("FontId");
	DWORD color				= GetColor(graphicElement->Attribute("Color"));

	myFonts.Add(myRenderer->AddFont(filePath,color));
	myFontIds.Add(fontId);

}

BlendModes GraphicsFactory::GetBlendMode(const char* aBlendMode)
{
	
	if(aBlendMode == NULL)
	{
		return BM_DEFAULT;
	}
	std::string blendMode = aBlendMode;
	if( "COLOR_ADD" == blendMode)
	{
		return BM_COLORADD;
	}
	if( "COLOR_MUL" == blendMode)
	{
		return BM_COLORMUL;
	}
	if("ALPHA_BLEND" == blendMode)
	{
		return BM_ALPHABLEND;
	}
	if("ALPHA_ADD" == blendMode)
	{
		return BM_ALPHAADD;
	}
	return BM_DEFAULT;
	

}
