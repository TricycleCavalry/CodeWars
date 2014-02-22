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
	delete myTileSprite;
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
	myFont->SetColor(ARGB(255,0,255,0));
	//myFont->SetScale(.f);
	
	LoadBlockTypes();
	CreateGrid();
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
		myTileSprite->SetColor(myBlocks[myTiles[i].myBlockId].first);
		myTileSprite->Render(myTiles[i].myX,myTiles[i].myY);
	}
	myHGE->Gfx_RenderLine(myPositionInGridX * myTileSize, myPositionInGridY * myTileSize, myPositionInGridX * myTileSize + 32, myPositionInGridY * myTileSize, 0xFFFF0000);
	myHGE->Gfx_RenderLine(myPositionInGridX * myTileSize, myPositionInGridY * myTileSize + 1, myPositionInGridX * myTileSize + 32, myPositionInGridY * myTileSize + 1, 0xFFFF0000);
	myHGE->Gfx_RenderLine(myPositionInGridX * myTileSize, myPositionInGridY * myTileSize + 32, myPositionInGridX * myTileSize + 32, myPositionInGridY * myTileSize + 32, 0xFFFF0000);
	myHGE->Gfx_RenderLine(myPositionInGridX * myTileSize, myPositionInGridY * myTileSize + 32 + 1, myPositionInGridX * myTileSize + 32, myPositionInGridY * myTileSize + 32 + 1, 0xFFFF0000);

	myHGE->Gfx_RenderLine(myPositionInGridX * myTileSize, myPositionInGridY * myTileSize, myPositionInGridX * myTileSize, myPositionInGridY * myTileSize + 32, 0xFFFF0000);
	myHGE->Gfx_RenderLine(myPositionInGridX * myTileSize + 1, myPositionInGridY * myTileSize, myPositionInGridX * myTileSize + 1, myPositionInGridY * myTileSize + 32, 0xFFFF0000);
	myHGE->Gfx_RenderLine(myPositionInGridX * myTileSize + 32, myPositionInGridY * myTileSize, myPositionInGridX * myTileSize + 32, myPositionInGridY * myTileSize + 32, 0xFFFF0000);
	myHGE->Gfx_RenderLine(myPositionInGridX * myTileSize + 32 + 1, myPositionInGridY * myTileSize, myPositionInGridX * myTileSize + 32 + 1, myPositionInGridY * myTileSize + 32, 0xFFFF0000);
	/*myPositionInGridSprite->Render(myPositionInGridX*myTileSize,myPositionInGridY*myTileSize);*/
	myFont->Render( 500, 75, HGETEXT_LEFT, "Current tile type:" );
	myFont->Render( 500, 100, HGETEXT_LEFT, myBlocks[myTiles[myPositionInGridX + myPositionInGridY*myHeight].myBlockId].second.c_str() );
}

void Editor::LoadBlockTypes()
{
	tinyxml2::XMLDocument* blocktypes = new tinyxml2::XMLDocument();
	blocktypes->LoadFile("Data\\XML\\BlockTypes.xml");

	tinyxml2::XMLElement* block = blocktypes->FirstChildElement();
	block = block->FirstChildElement();

	myTileSprite = new hgeSprite(0,0,0,32.f,32.f);

	while(block!=NULL)
	{
		std::string blockType = block->Attribute("Id");
		Vector4f spriteColor = XMLUTIL::GetVector4(block->Attribute("Color"),Vector4f(1,1,1,1));;

		myBlocks.Add(std::pair<DWORD,std::string>(ARGB(spriteColor.a,spriteColor.r,spriteColor.g,spriteColor.b),blockType));
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

		std::string tile = CommonUtilities::GetString("%i",myTiles[i].myX/32) + " " + CommonUtilities::GetString("%i",myTiles[i].myY/32);

		tileElement->SetAttribute("Tile",tile.c_str());

		levelElement->InsertEndChild(tileElement);
	}

	doc->InsertEndChild(levelElement);

	doc->SaveFile(aFile.c_str());
}