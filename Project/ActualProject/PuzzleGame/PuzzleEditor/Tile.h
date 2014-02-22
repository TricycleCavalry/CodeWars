#ifndef _TILE_H_
#define _TILE_H_

enum TileTypeEnum
{
	TTE_NORMAL,
	TTE_BLOCKED,
	TTE_NUM
};

struct Tile
{
	int myX;
	int myY;
	TileTypeEnum myType;
};

#endif