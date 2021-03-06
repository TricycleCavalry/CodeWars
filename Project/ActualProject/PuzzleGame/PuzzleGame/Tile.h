#ifndef _TILE_HEADER_
#define _TILE_HEADER_

#include "GrowingArray.h"
#include "SpriteWrapper.h"
#include "Vector2.h"

class Block;

enum TileType
{
	TT_NULL = -1,
	TT_NORMAL,
	TT_WIN,
	TT_NR_OF_TYPES,
};

class Tile
{
public:
	Tile(void);
	~Tile(void);

	void Init();

	void SetPosition(const Vector2<int>& aPosition);
	void SetTileType(const TileType& aTileType);
	void SetSprite(SpriteWrapper aSpriteWrapper);
	SpriteWrapper& GetSprite();

	void Update(const float& anElapsedTime);
	void Render(const Vector2<float> &aCameraPosition);

	Vector2<float> GetPosition();

	void Exit();

	GrowingArray<Block*>& GetBlocks();

	TileType GetTileType();
private:
	TileType myType;
	GrowingArray<Block*> myBlocks;
	Vector2<int> myPosition;
	SpriteWrapper mySprite;
	SpriteWrapper myBlinkSprite;
	float myBlinkTime;
};

#endif