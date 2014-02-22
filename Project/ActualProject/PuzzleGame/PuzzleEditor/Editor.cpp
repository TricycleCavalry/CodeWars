#include "stdafx.h"
#include "Editor.h"
#include "hge.h"
#include "hgesprite.h"
#include "InputHandler.h"
#include "hgefont.h"
#include "FI_File.h"
#include "XMLUTIL.h"


Editor::Editor(void)
:	myBlocks(64)
{
}


Editor::~Editor(void)
{
	//delete blocks.
	delete myPositionInGridSprite;
}

void Editor::Init( HGE *aHGE )
{
	myPositionInGridX = 0;
	myPositionInGridY = 0;
	myHGE = aHGE;
	myWidth = 10;
	myHeight = 10;
	myTileSize = 32;
	myTiles.Init( myWidth * myHeight );
	myBlocks.Init(64);
	
	myFont = new hgeFont( "font1.fnt" );
	
	LoadBlockTypes();
	CreateGrid();

	HTEXTURE texGridPosition = myHGE->Texture_Load("Data\\GFX\\Editor\\TilePosition.png");
	myPositionInGridSprite = new hgeSprite( texGridPosition, 0.f,0.f,myHGE->Texture_GetWidth(texGridPosition),myHGE->Texture_GetHeight(texGridPosition) );
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
	else if( InputKeyState(DIK_P,DIKS_CLICKED) )
	{
		SaveFile("Data\\XML\\Levels\\newLevel.xml");
	}
	CheckInputOnTile(DIK_UPARROW,1);
	CheckInputOnTile(DIK_DOWNARROW,-1);
	return true;
}

void Editor::Render()
{
	for( int i = 0, count = myTiles.Count(); i < count; ++i )
	{
		myBlocks[myTiles[i].myBlockId].first->Render(myTiles[i].myX,myTiles[i].myY);
	}
	myPositionInGridSprite->Render(myPositionInGridX*myTileSize,myPositionInGridY*myTileSize);
	//myFont->Render( 800, 75, HGETEXT_LEFT, "Current tile type:" );
	//myFont->Render( 800, 100, HGETEXT_LEFT, myTileInfo[myTiles[myPositionInGridX + myPositionInGridY*myHeight].myType].myType.c_str() );
}

void Editor::LoadBlockTypes()
{
	tinyxml2::XMLDocument* blocktypes = new tinyxml2::XMLDocument();
	blocktypes->LoadFile("Data\\XML\\BlockTypes.xml");

	tinyxml2::XMLElement* block = blocktypes->FirstChildElement();
	block = block->FirstChildElement();

	while(block!=NULL)
	{
		std::string blockType = block->Attribute("Id");
		std::string spritePath = block->Attribute("Sprite");
		HTEXTURE tex = myHGE->Texture_Load(spritePath.c_str());
		hgeSprite *sprite = new hgeSprite( tex, 0.f,0.f,myHGE->Texture_GetWidth(tex),myHGE->Texture_GetHeight(tex) );
		myBlocks.Add(std::pair<hgeSprite*,std::string>(sprite,blockType));
		block = block->NextSiblingElement();
	}
}

void Editor::CheckInputOnTile( const BYTE &aKey, int anIntegerToIncreaseWith )
{
	if( InputKeyState(aKey,DIKS_CLICKED) == false )
	{
		return;
	}
	int type = myTiles[myPositionInGridX + myPositionInGridY*myHeight].myBlockId;
	type += anIntegerToIncreaseWith;
	if( type >= myBlocks.Count() )
	{
		type = 0;
	}
	if( type < 0 )
	{
		type = myBlocks.Count()-1;
	}
	myTiles[myPositionInGridX + myPositionInGridY*myHeight].myBlockId = type;
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
				tile.myBlockId = 0;
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
	tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
	tinyxml2::XMLElement* levelElement = doc->NewElement("Level");

	std::string dimensions = CommonUtilities::GetString("%i",myWidth) + " " + CommonUtilities::GetString("%i",myHeight);
	levelElement->SetAttribute("GridDimensions",dimensions.c_str());

	tinyxml2::XMLElement* tileElement = NULL;

	for(int i = 0, count = myTiles.Count(); i < count; ++i )
	{
		tileElement = doc->NewElement("Block");
		tileElement->SetAttribute("BlockId",myBlocks[myTiles[i].myBlockId].second.c_str());

		std::string tile = CommonUtilities::GetString("%i",myTiles[i].myX) + " " + CommonUtilities::GetString("%i",myTiles[i].myY);

		tileElement->SetAttribute("Tile",tile.c_str());

		levelElement->InsertEndChild(tileElement);
	}

	doc->InsertEndChild(levelElement);

	doc->SaveFile(aFile.c_str());
}