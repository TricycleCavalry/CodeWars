#ifndef _TILE_INFO_HEADER_
#define _TILE_INFO_HEADER_

#define NULL 0

class Tile;
class Block;

struct TileInfo
{
	Tile* myTile;
	Block* myBlock;

	bool HasBlock()
	{
		return myBlock != NULL;
	}
};

#endif