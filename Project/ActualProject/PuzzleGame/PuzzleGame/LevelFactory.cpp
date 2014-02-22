#include "LevelFactory.h"

#include "Level.h"
#include "XMLUtil.h"
#include "Root.h"
#include "Block.h"

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
		blockId = XMLUTIL::GetString(blockIterator,"BlockId");
		blockTilePosF = XMLUTIL::GetVector2(blockIterator,"Tile");
		blockTilePos = Vector2<int>(static_cast<int>(blockTilePosF.x),static_cast<int>(blockTilePosF.y));
		
		currentTile = aLevel->GetTile(blockTilePos);
		if(currentTile == NULL)
		{
			DL_DEBUG("The block with the id: %s has a tile that doesn't exist (x: %d, y: %d)",blockId.c_str(),blockTilePos.x,blockTilePos.y);
		}
		else
		{
			Block* block = FACTORIES.myBlockFactory.GetBlock(blockId.c_str());
			block->Init(blockTilePosF*32.f,Vector2f(32.f,32.f));
			currentTile->GetBlocks().Add(block);
			block->OnEnter(currentTile);
		}

		blockIterator = blockIterator->NextSiblingElement();
	}
}