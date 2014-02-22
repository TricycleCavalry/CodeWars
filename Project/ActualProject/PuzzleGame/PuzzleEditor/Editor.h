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

	void SaveFile( const std::string &aFile );

private:
	void CreateGrid();
	void InitSprites();
	void InitTileInfo();

	void CheckInputOnTile( const BYTE &aKey, int anIntegerToIncreaseWith );

	float myWidth;
	float myHeight;
	float myTileSize;
	GrowingArray<Tile> myTiles;
	GrowingArray<hgeSprite*> mySprites;
	GrowingArray<TileInfo> myTileInfo;
	hgeSprite *myPositionInGridSprite;
	int myPositionInGridX;
	int myPositionInGridY;
	HGE *myHGE;
	hgeFont *myFont;
};

#endif