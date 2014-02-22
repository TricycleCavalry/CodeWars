#ifndef _LEVEL_HEADER_
#define _LEVEL_HEADER_

#include "GrowingArray.h"
#include "Vector2.h"

#include "Tile.h"

#define TILE_WIDTH 32	//NoNeed
#define TILE_HEIGHT 32  //NoNeed
#define TILE_SIZE 32

class Level
{
	friend class LevelFactory;
public:
	Level(void);
	~Level(void);

	void Init(const Vector2<int>& someDimensions);
	void Update(const float& anElapsedTime);
	void Render(const Vector2<float>& aCameraPosition);

	Tile* GetTile(const Vector2<int>& aTilePosition);
	Tile* GetTile(const Vector2<float>& aPosition);

	void SetHGE(HGE* aHGE);

private:
	void RenderLine(const float aX1,const float aY1,const float aX2,const float aY2 ,const Vector4<float>& aColor);
	int GetIndexForPosition(const Vector2<int>& aPosition);
private:
	HGE* myHGE;

	Vector2<int> myDimensions;

	GrowingArray<Tile> myTiles;
};

#endif