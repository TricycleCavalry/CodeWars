#include "stdafx.h"
#include "Editor.h"
#include "hge.h"
#include "hgesprite.h"
#include "InputHandler.h"
#include "hgefont.h"
#include "FI_File.h"


Editor::Editor(void)
{
}


Editor::~Editor(void)
{
	mySprites.DeleteAll();
	delete myPositionInGridSprite;
}

void Editor::Init( HGE *aHGE )
{
	myPositionInGridX = 0;
	myPositionInGridY = 0;
	myHGE = aHGE;
	myWidth = 10;
	myHeight = 10;
	myTileSize = 64;
	myTiles.Init( myWidth * myHeight );
	mySprites.Init( 5 );
	myTileInfo.Init( 5 );
	
	myFont = new hgeFont( "font1.fnt" );
	
	
	CreateGrid();
	InitSprites();
	InitTileInfo();
}

void Editor::InitSprites()
{
	HTEXTURE tex = myHGE->Texture_Load("TileNormal.png");
	hgeSprite *sprite = new hgeSprite( tex, 0.f,0.f,myHGE->Texture_GetWidth(tex),myHGE->Texture_GetHeight(tex) );
	mySprites.Add(sprite);
	HTEXTURE texBlocked = myHGE->Texture_Load("TileBlocked.png");
	hgeSprite *blockedSprite = new hgeSprite( texBlocked, 0.f,0.f,myHGE->Texture_GetWidth(texBlocked),myHGE->Texture_GetHeight(texBlocked) );
	mySprites.Add(blockedSprite);
	HTEXTURE texGridPosition = myHGE->Texture_Load("TilePosition.png");
	myPositionInGridSprite = new hgeSprite( texGridPosition, 0.f,0.f,myHGE->Texture_GetWidth(texGridPosition),myHGE->Texture_GetHeight(texGridPosition) );
}

void Editor::InitTileInfo()
{
	for( int i = 0; i < TTE_NUM; ++i )
	{
		TileInfo info;
		info.myType = "";
		myTileInfo.Add(info);
	}
	
	myTileInfo[0].myType = "Ice!";
	myTileInfo[1].myType = "Blocked!";
}

bool Editor::Update()
{
	if( InputKeyState(DIK_D,DIKS_CLICKED) )
	{
		if( myPositionInGridX % (int)myWidth != myWidth-1 )
		{
			++myPositionInGridX;
		}
	}
	else if( InputKeyState(DIK_A,DIKS_CLICKED) )
	{
		if( myPositionInGridX % (int)myWidth != 0 )
		{
			--myPositionInGridX;
		}
	}
	else if( InputKeyState(DIK_S,DIKS_CLICKED) )
	{
		if( myPositionInGridY % (int)myHeight != myWidth-1 )
		{
			++myPositionInGridY;
		}
	}
	else if( InputKeyState(DIK_W,DIKS_CLICKED) )
	{
		if( myPositionInGridY % (int)myHeight != 0 )
		{
			--myPositionInGridY;
		}
	}
	CheckInputOnTile(DIK_UPARROW,1);
	CheckInputOnTile(DIK_DOWNARROW,-1);
	return true;
}

void Editor::Render()
{
	for( int i = 0, count = myTiles.Count(); i < count; ++i )
	{
		mySprites[myTiles[i].myType]->Render(myTiles[i].myX,myTiles[i].myY);
	}
	myPositionInGridSprite->Render(myPositionInGridX*myTileSize,myPositionInGridY*myTileSize);
	myFont->Render( 800, 75, HGETEXT_LEFT, "Current tile type:" );
	myFont->Render( 800, 100, HGETEXT_LEFT, myTileInfo[myTiles[myPositionInGridX + myPositionInGridY*myHeight].myType].myType.c_str() );
}

void Editor::CheckInputOnTile( const BYTE &aKey, int anIntegerToIncreaseWith )
{
	if( InputKeyState(aKey,DIKS_CLICKED) == false )
	{
		return;
	}
	int type = myTiles[myPositionInGridX + myPositionInGridY*myHeight].myType;
	type += anIntegerToIncreaseWith;
	if( type >= TTE_NUM )
	{
		type = 0;
	}
	if( type < 0 )
	{
		type = TTE_NUM-1;
	}
	myTiles[myPositionInGridX + myPositionInGridY*myHeight].myType = (TileTypeEnum)type;
}

void Editor::CreateGrid()
{
	if( myTiles.Count() == 0 )
	{
		for( int y = 0; y < myHeight; ++y )
		{
			for( int x = 0; x < myWidth; ++x )
			{
				Tile tile;
				tile.myType = TTE_NORMAL;
				tile.myX = x * myTileSize;
				tile.myY = y * myTileSize;
				myTiles.Add( tile );
			}
		}
	}
	/*for( int y = 0; y < myHeight; ++y )
		{
			for( int x = 0; x < myWidth; ++x )
			{
				Tile tile;
				myTiles[x + y * myHeight].myType = TTE_NORMAL;
				myTiles[x + y * myHeight].myX = x * myTileSize;
				myTiles[x + y * myHeight].myY = y * myTileSize;
				myTiles.Add( tile );
			}
		}*/
}

void Editor::SaveFile( const std::string &aFile )
{
	File file;
	file.Open( aFile, 1 << WRITE );
	for( int i = 0, count = myTiles.Count(); i < count; ++i )
	{
		file.WriteInt( myTiles[i].myType );
	}
}