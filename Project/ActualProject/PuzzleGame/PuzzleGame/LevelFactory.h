#ifndef LEVEL_FACTORY_HEADER
#define LEVEL_FACTORY_HEADER

#include <string>
#include "XMLUtil.h"
#include "GrowingArray.h"

class Level;
class Block;
class Tile;

class LevelFactory
{
public:
	LevelFactory();
	~LevelFactory();
	
	Level* CreateLevel(const std::string& aFilepath);
private:
	void CreateTiles(GrowingArray<Tile*>& someTiles, XmlElement& anXMLListElement);
	void CreateBlocks(GrowingArray<Block*>& someBlocks);
private:
	std::string myCurrentLevelpath;
};

#endif