#include "StdAfx.h"
#include "Level.h"

#include "Tile.h"
#include "Block.h"
#include "Root.h"
#include "hge.h"



Level::Level(void)
:	myTiles(256)
,	myHGE(NULL)
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

void Level::Render(const Vector2<float>& aCameraPosition)
{
	for(int i=0,count=myTiles.Count();i<count;i++)
	{
		myTiles[i].Render(aCameraPosition);
	}
	/*for(int x = 0; x < myDimensions.x; ++x)
	{
		for(int  y = 0; y < myDimensions.y; ++y)
		{
			RenderLine(0,
		}
	}*/
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
Tile* Level::GetTile(const Vector2<float>& aPosition)
{
	Vector2<int> pos(aPosition.x,aPosition.y);
	pos/= TILE_SIZE;
	return GetTile(pos);
}
void Level::SetHGE(HGE* aHGE)
{
	myHGE = aHGE;
}
void Level::RenderLine(const float aX1,const float aY1,const float aX2,const float aY2 ,const Vector4<float>& aColor)
{
	DWORD color = ARGB(aColor.a,aColor.r,aColor.g,aColor.b);
	myHGE->Gfx_RenderLine(aX1,aY1,aX2,aY2,color);

}
int Level::GetIndexForPosition(const Vector2<int>& aPosition)
{
	int indexToReturn = -1;
	if(aPosition.x >= 0 && aPosition.x < myDimensions.x)
	{
		indexToReturn = aPosition.x;
		
	}
	else
	{
		return -1;
	}
	if(aPosition.y >= 0 && aPosition.y < myDimensions.y)
	{
		if(indexToReturn == -1)
		{
			indexToReturn = 0;
		}
		indexToReturn += aPosition.y * myDimensions.x;
	}
	else
	{
		return -1;
	}
	return indexToReturn;
}