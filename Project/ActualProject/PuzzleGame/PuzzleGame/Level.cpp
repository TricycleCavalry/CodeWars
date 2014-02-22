#include "StdAfx.h"
#include "Level.h"

#include "Tile.h"
#include "Block.h"
#include "Root.h"

#define TILE_WIDTH 32
#define TILE_HEIGHT 32

Level::Level(void)
:	myTiles(256)
{
}

Level::~Level(void)
{
}

void Level::Init(const Vector2<int>& someDimensions)
{
	myDimensions = someDimensions;
	int counter = 0;
	for(int y=0;y<myDimensions.y;y++)
	{
		for(int x=0;x<myDimensions.x;x++)
		{
			myTiles.Add(Tile());
			myTiles[counter].Init();
			myTiles[counter].SetTileType(TT_NORMAL);
			myTiles[counter].SetSprite(ROOT->GetManagers().mySpriteManager.GetSprite("Data\\GFX\\Tiles\\tile01.png"));
			myTiles[counter].SetPosition(Vector2<int>(x*TILE_WIDTH,y*TILE_HEIGHT));
			counter++;
		}
	}
}

void Level::Update(const float& anElapsedTime)
{
	for(int i=0,count=myTiles.Count();i<count;i++)
	{
		myTiles[i].Update(anElapsedTime);
	}
}

void Level::Render()
{
	for(int i=0,count=myTiles.Count();i<count;i++)
	{
		myTiles[i].Render();
	}
}

Tile* Level::GetTile(const Vector2<int>& aTilePosition)
{
	Tile* returnTile = NULL;
	int index = GetIndexForPosition(aTilePosition);
	if(index != -1)
	{
		returnTile = &myTiles[index];
	}
	return returnTile;
}

int Level::GetIndexForPosition(const Vector2<int>& aPosition)
{
	int indexToReturn = -1;
	if(aPosition.x >= 0 && aPosition.x < myDimensions.x)
	{
		indexToReturn = aPosition.x;
	}
	if(aPosition.y >= 0 && aPosition.y < myDimensions.y)
	{
		if(indexToReturn == -1)
		{
			indexToReturn = 0;
		}
		indexToReturn += aPosition.y * myDimensions.x;
	}
	return indexToReturn;
}