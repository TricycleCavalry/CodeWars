#include "StdAfx.h"
#include "Tile.h"

Tile::Tile(void)
:	myType(TT_NULL)
{
}

Tile::~Tile(void)
{
}

void Tile::Init()
{
	myBlocks.Init(8);
}

void Tile::SetPosition(const Vector2<int>& aPosition)
{
	myPosition = aPosition;
}

void Tile::SetTileType(const TileType& aTileType)
{
	myType = aTileType;
}

void Tile::SetSprite(SpriteWrapper aSpriteWrapper)
{
	mySprite = aSpriteWrapper;
}

void Tile::Update(const float& anElapsedTime)
{
	
}

void Tile::Render(const Vector2<float> &aCameraPosition)
{
	Vector2<int> camPos(aCameraPosition.myX, aCameraPosition.myY);
	mySprite.Render(myPosition - camPos);
}

GrowingArray<Block*>& Tile::GetBlocks()
{
	return myBlocks;
}