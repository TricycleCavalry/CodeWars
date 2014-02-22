#include "LevelFactory.h"

#include "Level.h"
#include "XMLUtil.h"
#include "Root.h"

LevelFactory::LevelFactory()
{

}

LevelFactory::~LevelFactory()
{
	
}

Level* LevelFactory::CreateLevel(const std::string& aFilepath)
{
	Level* newLevel = new Level();
	myCurrentLevelFilePath = aFilepath;

	tinyxml2::XMLElement* levelElement = XMLUTIL::LoadFile(myCurrentLevelFilePath);

	Vector2f gridDimensionsF = XMLUTIL::GetVector2(levelElement,"GridDimensions");
	Vector2<int> gridDimenions(static_cast<int>(gridDimensionsF.x),static_cast<int>(gridDimensionsF.y));
	newLevel->Init(gridDimenions);

	CreateBlocks(newLevel,levelElement->FirstChildElement("Block"));
	
	return newLevel;
}

void LevelFactory::CreateBlocks(Level* aLevel, tinyxml2::XMLElement* aBlockElement)
{
	tinyxml2::XMLElement* blockIterator = aBlockElement;

	std::string blockId;
	Vector2f blockTilePosF;
	Vector2<int> blockTilePos;
	Tile* currentTile = NULL;
	while(blockIterator != NULL)
	{
		blockId = XMLUTIL::GetString(aBlockElement,"BlockId");
		blockTilePosF = XMLUTIL::GetVector2(aBlockElement,"Tile");
		blockTilePos = Vector2<int>(static_cast<int>(blockTilePosF.x),static_cast<int>(blockTilePosF.y));
		
		currentTile = aLevel->GetTile(blockTilePos);
		if(currentTile == NULL)
		{
			DL_DEBUG("The block with the id: %s has a tile that doesn't exist (x: %d, y: %d)",blockId.c_str(),blockTilePos.x,blockTilePos.y);
		}
		else
		{
			currentTile->GetBlocks().Add(FACTORIES.myBlockFactory.GetBlock(blockId.c_str()));
		}

		blockIterator = blockIterator->NextSiblingElement();
	}
}