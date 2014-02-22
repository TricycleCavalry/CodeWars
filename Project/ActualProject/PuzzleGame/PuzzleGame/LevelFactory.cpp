#include "LevelFactory.h"

#include "Level.h"

LevelFactory::LevelFactory()
{

}

LevelFactory::~LevelFactory()
{
	
}

Level* LevelFactory::CreateLevel(const std::string& aFilepath)
{
	Level* newLevel = new Level();
	myCurrentLevelpath = aFilepath;

	XmlDoc* xmlDoc = new XmlDoc();
	xmlDoc->LoadFile(aFilepath.c_str());

	//CreateTiles(newLevel->myTiles,*xmlDoc->FirstChildElement("AttributeList"));
	
	return newLevel;
}

void LevelFactory::CreateTiles(GrowingArray<Tile*>& someTiles, XmlElement& anXMLListElement)
{
	//TODO
}
void LevelFactory::CreateBlocks(GrowingArray<Block*>& someBlocks, XmlElement& anXMLListElement)
{
	//TODO
}