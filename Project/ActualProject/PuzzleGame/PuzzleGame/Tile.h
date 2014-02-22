#ifndef _TILE_HEADER_
#define _TILE_HEADER_

enum TileType
{
	TT_NULL = -1,
	TT_NORMAL,
	TT_NR_OF_TYPES,
};

class Tile
{
public:
	Tile(const TileType& aTileType);
	~Tile(void);

	void SetTileType(const TileType& aTileType);

	void Update(const float& anElapsedTime);
	void Render();
private:
	TileType myType;
};

#endif