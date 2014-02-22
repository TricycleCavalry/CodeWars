#ifndef _RENDER_DATA_H_
#define _RENDER_DATA_H_

#include "Vector2.h"
#include "Rect.h"
#include <string>

struct FontRenderData
{
	int				myFontId;
	DWORD			myColor;
	std::string		myText;
	Vector2<double>	myPosition;
	float			myLayer;
	float			myBoxWidth;
	float			myBoxHeight;
	float			myRotation;
	float			myScale;
	int				myAlignment;
	


};
struct RenderData
{
	int mySpriteID;
	int myBlendMode;
	DWORD myColor;
	float myLayer;
	Vector2<double> myOrgin;
	Rect mySpriteSheetRect;

	float myRotation;
	float myXScale;
	float myYScale;
	Vector2<double> myPosition;	
	bool myIsUI;
	
};

struct MeshRenderData
{
	int myMeshID;
	int myBlendMode;
	DWORD myColor;
	float myLayer;
	Rect mySpriteSheetRect;
	Vector2<double> myPosition;
	float myBaseHeight;
	float myTopHeight;
	int mySide;
	Vector2<double> myDimensions;
	bool myIsUI;
};

enum WallSides
{
	W_ROOF = -1,
	W_NORTH,
	W_SOUTH,
	W_WEST,
	W_EAST,
	W_WALL,
};
#endif