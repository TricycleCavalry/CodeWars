#ifndef _TILE_HEADER_
#define _TILE_HEADER_

#include "GrowingArray.h"

class Block;

enum TileType
{
	TT_NULL = -1,
	TT_NORMAL,
	TT_NR_OF_TYPES,
};

class Tile
{
public:
	Tile(void);
	~Tile(void);

	void Init();

	void SetTileType(const TileType& aTileType);

	void Update(const float& anElapsedTime);
	void Render();

	GrowingArray<Block*>& GetBlocks();
private:
	TileType myType;
	GrowingArray<Block*> myBlocks;
};

#endif