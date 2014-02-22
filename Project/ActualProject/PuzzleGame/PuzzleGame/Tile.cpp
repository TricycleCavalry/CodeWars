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

void Tile::SetTileType(const TileType& aTileType)
{
	myType = aTileType;
}

void Tile::Update(const float& anElapsedTime)
{
	
}

void Tile::Render()
{
	
}

GrowingArray<Block*>& Tile::GetBlocks()
{
	return myBlocks;
}