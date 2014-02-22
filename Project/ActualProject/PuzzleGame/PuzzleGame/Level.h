#ifndef _LEVEL_HEADER_
#define _LEVEL_HEADER_

#include "GrowingArray.h"
#include "Vector2.h"

#include "Tile.h"

class Level
{
	friend class LevelFactory;
public:
	Level(void);
	~Level(void);

	void Init(const Vector2<int>& someDimensions);

	void Update(const float& anElapsedTime);
	void Render();

	Tile* GetTile(const Vector2<int>& aTilePosition);

private:
	int GetIndexForPosition(const Vector2<int>& aPosition);

	Vector2<int> myDimensions;

	GrowingArray<Tile> myTiles;
};

#endif