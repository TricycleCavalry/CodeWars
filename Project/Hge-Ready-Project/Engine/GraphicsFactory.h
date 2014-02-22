#ifndef _GrAPHICS_FACTORY_H_
#define _GrAPHICS_FACTORY_H_
#include "BaseFactory.h"
#include "tinyxml2.h"

class TimeManager;
class Sprite;
class Font;

class GraphicsFactory : public BaseFactory
{
public:
	GraphicsFactory(void);
	~GraphicsFactory(void);

	void Init(Renderer* aRenderer,TimeManager* aTimeManager);

	void LoadSpriteSheets(tinyxml2::XMLDocument* aXMLDocument);

	void LoadGraphics(tinyxml2::XMLDocument* aXMLDocument);
	void LoadGraphics(tinyxml2::XMLElement* aXMLElement);

	Graphic*	GetGraphic(const std::string& aGraphicId);
	Font*		GetFont(const std::string& aFontId);


private:
	Renderer* myRenderer;
	TimeManager* myTimeManager;
	GrowingArray<Graphic*> myGraphics;
	GrowingArray<std::string> myGraphicsIds;

	GrowingArray<Font*> myFonts;
	GrowingArray<std::string> myFontIds;



	void LoadGraphic(tinyxml2::XMLElement* aXMLElement);
	GraphicTypes GetGraphicType(const std::string& aType);

	void LoadSprite(tinyxml2::XMLElement* aXMLElement);
	void LoadStaticAnimation(tinyxml2::XMLElement* aXMLElement);
	void LoadDynamicAnimation(tinyxml2::XMLElement* aXMLElement);
	void LoadDistortionMesh(tinyxml2::XMLElement* aXMLElement);
	void LoadFont(tinyxml2::XMLElement* aXMLElement);

	BlendModes GetBlendMode(const char* aBlendMode);

	
};

#endif