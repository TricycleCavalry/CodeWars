#include "StdAfx.h"
#include "Tile.h"

#include "Block.h"
#include "CommonMacros.h"
#include "Root.h"

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
	myBlinkSprite = ROOT->GetManagers().mySpriteManager.GetSprite("");
	myBlinkSprite.SetColor(ARGB(0,255,255,255));
	myBlinkSprite.SetZ(0.9f);
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
	mySprite.SetZ(1.f);
}
SpriteWrapper& Tile::GetSprite()
{
	return mySprite;
}

void Tile::Update(const float& anElapsedTime)
{
	myBlinkTime = MAX(myBlinkTime-anElapsedTime*5,0.f);
	if(myBlinkTime > 0.f)
	{
		myBlinkSprite.SetColor(ARGB(125*(sin(myBlinkTime*M_PI)+1.25)/4,0,0,0));
	}
	else
	{
		myBlinkSprite.SetColor(ARGB(0,255,255,255));
	}
}

void Tile::Render(const Vector2<float> &aCameraPosition)
{
	Vector2<int> camPos(aCameraPosition.myX, aCameraPosition.myY);
	mySprite.Render(myPosition - camPos);
	myBlinkSprite.Render(myPosition-camPos);
}
Vector2<float> Tile::GetPosition()
{
	return Vector2<float>(myPosition.x,myPosition.y);
}
void Tile::Exit()
{
	myBlinkTime = 1.f;
}
GrowingArray<Block*>& Tile::GetBlocks()
{
	return myBlocks;
}
TileType Tile::GetTileType()
{
	return myType;
}