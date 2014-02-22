#ifndef _EDITOR_H_
#define _EDITOR_H_

#include "Tile.h"
#include "GrowingArray.h"
#include "TileInfo.h"

class hgeSprite;
class HGE;
class hgeFont;
class InputHandler;

class Editor
{
public:
	Editor(void);
	~Editor(void);

	void Init( HGE *aHGE );
	bool Update();
	void Render();

	void LoadBlockTypes();

	void SaveFile( const std::string &aFile );

private:
	void CreateGrid();

	void CheckInputOnTile( const BYTE &aKey, int anIntegerToIncreaseWith );

	int myWidth;
	int myHeight;
	float myTileSize;
	GrowingArray<Tile> myTiles;
	GrowingArray<std::pair<DWORD,std::string>> myBlocks;
	int myPositionInGridX;
	int myPositionInGridY;
	HGE *myHGE;
	hgeSprite* myTileSprite;
	hgeFont *myFont;
};

#endif