#pragma warning (disable:4005)
#include "Renderer.h"

#include "Debug.h"
#include <string>
#include "hgeSprite.h"
#include "hgedistort.h"
#include "DistortionMesh.h"
#include "Sprite.h"
#include "CommonMacros.h"
#include "Corners.h"
#include "Font.h"
#include "Camera.h"



Renderer::Renderer(HGE* aHGE)
:	myHGE(aHGE)
,	myCameraPosition(NULL)
,	myLoadedFiles(2,true)
,	myTextures(2)
,	myFontPaths(2,true)
,	myFonts(2)
,	myTextureIds(2,true)
,	myWindowWidth(0)
,	myWindowHeight(0)
,	myZ(1)
,	myCamera(NULL)

{
}

Renderer::~Renderer(void)
{
}
bool Renderer::Init()
{
	myCurrentRenderingQueue = 1;
	myCurrentBuildingQueue = 0;
	myRenderingQueues[0].Init(32);
	myRenderingQueues[1].Init(32);
	myMeshRenderingQueues[0].Init(32);
	myMeshRenderingQueues[1].Init(32);
	myFontRenderingQueues[0].Init(32);
	myFontRenderingQueues[1].Init(32);
	myWindowWidth  = myHGE->System_GetState(HGE_SCREENWIDTH);
	myWindowHeight = myHGE->System_GetState(HGE_SCREENHEIGHT);



	return true;
}
bool Renderer::Render()
{
	myHGE->Gfx_BeginScene();
	myHGE->Gfx_Clear(0);

	Vector2<double> cameraPos;

	if(myCameraPosition != NULL)
	{
		cameraPos = Vector2<double>(floor(myCameraPosition->x),floor(myCameraPosition->y));
	}
	else
	{
		cameraPos = Vector2<double>(0,0);
	}

	for(int i = 0; i < myMeshRenderingQueues[myCurrentRenderingQueue].Count(); ++i)
	{
		RenderMesh(myMeshRenderingQueues[myCurrentRenderingQueue][i],cameraPos);
	}
	SortRenderData(myRenderingQueues[myCurrentRenderingQueue]);
	for(int i = 0; i < myRenderingQueues[myCurrentRenderingQueue].Count(); ++i)
	{
		RenderSprite(myRenderingQueues[myCurrentRenderingQueue][i],cameraPos);
	}
	for(int i = 0; i < myFontRenderingQueues[myCurrentRenderingQueue].Count(); ++i)
	{
		RenderFont(myFontRenderingQueues[myCurrentRenderingQueue][i]);
	}


	myHGE->Gfx_EndScene();
	return true;
}

void Renderer::AddTexture(const std::string& aFilePath,const std::string& aTextureId)
{	
	HTEXTURE texture = GetLoadedTexture(aFilePath,aTextureId);
	if(texture == NULL)
	{		
		AddHGESprite(aFilePath,aTextureId);	
		return;
	}
	else
	{
		int id = GetSpriteId(aTextureId);
		for( std::map<int,hgeSprite*>::iterator i = myHGESprites.begin(); i != myHGESprites.end(); i ++)
		{
			if(i->first == id)
			{
				DL_CRITICAL("Unnecessary file load! : \n filepath: %s \n textureId: %s",aFilePath,aTextureId);
				DL_ASSERT("Unnecessary file load!");
			}
		}
		myHGESprites[id] = new hgeSprite(texture,0,0,TO_FLOAT(myHGE->Texture_GetWidth(texture)),TO_FLOAT(myHGE->Texture_GetHeight(texture)));
	}
}

void Renderer::AddMeshTexture(const std::string& aFilePath,const std::string& aTextureId)
{
	HTEXTURE texture = GetLoadedTexture(aFilePath,aTextureId);
	if(texture == NULL)
	{		
		AddHGEDistortionMesh(aFilePath,aTextureId);	
		return;
	}
	else
	{
		int id = GetSpriteId(aTextureId);
		for( std::map<int,hgeDistortionMesh*>::iterator i = myDistortionMeshes.begin(); i != myDistortionMeshes.end(); i ++)
		{
			if(i->first == id)
			{
				DL_CRITICAL("Unnecessary file load! : \n filepath: %s \n textureId: %s",aFilePath,aTextureId);
				DL_ASSERT("Unnecessary file load!");
			}
		}
		float width = TO_FLOAT(myHGE->Texture_GetWidth(texture));
		float height= TO_FLOAT(myHGE->Texture_GetHeight(texture));
		hgeDistortionMesh* newMesh = new hgeDistortionMesh(static_cast<int>(width)/64,static_cast<int>(height)/64);
		newMesh->SetTexture(texture);
		newMesh->SetTextureRect(0,0,width,height);
		myDistortionMeshes[id] = newMesh;
	}
}

Sprite* Renderer::AddSprite(const std::string& aTextureId,const Rect& aRect, const Vector2<float> aOrgin,const int aBlendMode, const float& aRotation)
{
	if(TextureIsLoaded(aTextureId) == true)
	{
		Sprite* returnSprite = new Sprite(*this);
		returnSprite->Init(GetSpriteId(aTextureId),aBlendMode,aRect, aOrgin,aRotation);
		return returnSprite;
	}
	DL_CRITICAL("Texture/SpriteSheet Path has not been loaded! \n Sprite \n TextureId: %s",aTextureId);
	DL_ASSERT("Texture/SpriteSheet path has not been loaded!");
	return NULL;

}

DistortionMesh* Renderer::AddMesh(const std::string&  aTextureId,const Rect& aRect, const int aBlendMode)
{
	if(TextureIsLoaded(aTextureId) == true)
	{
		DistortionMesh* returnMesh = new DistortionMesh(*this);
		returnMesh->Init(GetSpriteId(aTextureId),aBlendMode,aRect);
		return returnMesh;
	}
	DL_CRITICAL("Texture/SpriteSheet Path has not been loaded! \n\t Mesh, forgot IsMesh = \"true\"? \n\t TextureId: %s",aTextureId.c_str());
	DL_DEBUG(aTextureId);
	DL_ASSERT("Texture/SpriteSheet Path has not been loaded!");
	return NULL;
}

Font* Renderer::AddFont(const std::string aFilePath,const DWORD& aColor)
{
	if(FontIsLoaded(aFilePath) == false)
	{
		myFontPaths.Add(aFilePath);
		myFonts.Add(new hgeFont(aFilePath.c_str()));
	}
	
	int id = GetFontId(aFilePath);

	Font* returnFont = new Font(*this);
	returnFont->Init(id,aColor);
	
	return returnFont;
}

void Renderer::AddToRenderQueue(const Sprite& aSprite,const float aXPos,const float aYPos, const float aLayer,const float aRotation, const float aXScale, const float aYScale, const DWORD& aColor, bool aIsUIFlag)
{
	Sprite sprite = aSprite;
	RenderData renderData;
	renderData.mySpriteID		=	aSprite.myID;
	renderData.myBlendMode		=	aSprite.myBlendMode;
	renderData.myOrgin			=	Vector2<double>(aSprite.myOrgin.x,aSprite.myOrgin.y);
	renderData.mySpriteSheetRect=	aSprite.mySpriteSheetRect;
	renderData.myLayer			=	aLayer;
	renderData.myRotation		=	aRotation;
	renderData.myXScale			=	aXScale;
	renderData.myYScale			=	aYScale;	
	renderData.myPosition		=	Vector2<double>(aXPos,aYPos);
	renderData.myColor			=	aColor;
	renderData.myIsUI			=	aIsUIFlag;


	myRenderingQueues[myCurrentBuildingQueue].Add(renderData);
}


void Renderer::AddToRenderQueue(const DistortionMesh& aMesh, const float aXPos, const float aYPos, const float aLayer, const float& aBaseHeight, const float& aTopHeight, const WallSides& aSide, const float& aWidth, const float& aHeight, const DWORD& aColor, bool aIsUIFlag)
{
	MeshRenderData renderData;
	renderData.myMeshID			=	aMesh.myID;
	renderData.myBlendMode		=	aMesh.myBlendMode;
	renderData.myColor			=	aColor;
	renderData.mySpriteSheetRect=	aMesh.mySpriteSheetRect;
	renderData.myPosition		=	Vector2<double>(floor(aXPos),floor(aYPos));
	renderData.myBaseHeight		=	aBaseHeight;
	renderData.myTopHeight		=	aTopHeight;
	renderData.myLayer			=	aLayer;
	renderData.mySide			=	aSide;
	renderData.myDimensions		=	Vector2<double>(aWidth,aHeight);
	renderData.myIsUI			=	aIsUIFlag;

	myMeshRenderingQueues[myCurrentBuildingQueue].Add(renderData);
}

void Renderer::AddToRenderQueue(const Font& aFont,const float& aXPos,const float& aYPos, const float& aLayer,const float& aRotation, const float& aScale,const DWORD& aColor,const int& anAlignment, const std::string& aText,const float& aBoxWidth, const float& aBoxHeight)
{
	FontRenderData fontRenderData;
	fontRenderData.myFontId		= aFont.myId;
	fontRenderData.myColor		= aFont.myColor;

	fontRenderData.myPosition	= Vector2<double>(floor(aXPos),floor(aYPos));	
	fontRenderData.myLayer		= aLayer;
	fontRenderData.myRotation	= aRotation;
	fontRenderData.myScale		= aScale;
	fontRenderData.myText		= aText;
	fontRenderData.myAlignment	= anAlignment;
	fontRenderData.myBoxWidth	= aBoxWidth;
	fontRenderData.myBoxHeight	= aBoxHeight;

	myFontRenderingQueues[myCurrentBuildingQueue].Add(fontRenderData);
}

void Renderer::CleanQueue()
{	
	myRenderingQueues[myCurrentBuildingQueue].RemoveAll();
	myMeshRenderingQueues[myCurrentBuildingQueue].RemoveAll();
	myFontRenderingQueues[myCurrentBuildingQueue].RemoveAll();
}
void Renderer::SwitchQueues()
{
	int lastQueue = myCurrentRenderingQueue;
	myCurrentRenderingQueue = myCurrentBuildingQueue;
	myCurrentBuildingQueue = lastQueue;
}

hgeFont* Renderer::GetFont(const int& aId)
{
	return myFonts[aId];
}

void Renderer::SetCameraPosition(Vector2<float>* aCameraPosition)
{
	myCameraPosition = aCameraPosition;
}
void Renderer::SetCamera(Camera* aCamera)
{
	myCamera = aCamera;
}
void Renderer::SetWindowHeightPointers(Vector2<float*> someWindowDimensions)
{
	myWindowDimensions.x = someWindowDimensions.x;
	myWindowDimensions.y = someWindowDimensions.y;
	myOriginalDimensions.x = *someWindowDimensions.x;
	myOriginalDimensions.y = *someWindowDimensions.y;
}

void Renderer::ChangeZ(const double& aZ)
{
	myZ += aZ;
	*myWindowDimensions.x = myOriginalDimensions.x*static_cast<float>(myZ);
	*myWindowDimensions.y = myOriginalDimensions.y*static_cast<float>(myZ);
	if(myCamera != NULL)
	{
		myCamera->SetZ(static_cast<float>(myZ));
	}
}

void Renderer::SetZ(const double& aZ)
{
	myZ = aZ;
	*myWindowDimensions.x = myOriginalDimensions.x*static_cast<float>(myZ);
	*myWindowDimensions.y = myOriginalDimensions.y*static_cast<float>(myZ);
	if(myCamera != NULL)
	{
		myCamera->SetZ(static_cast<float>(myZ));
	}
}

void Renderer::SetHGE(HGE* aHGE)
{
	myHGE = aHGE;
	myWindowWidth  = myHGE->System_GetState(HGE_SCREENWIDTH);
	myWindowHeight = myHGE->System_GetState(HGE_SCREENHEIGHT);
}

void Renderer::RenderSprite(const RenderData& someRenderData,const Vector2<double>& aCameraPos)
{
	myHGESprites[someRenderData.mySpriteID]->SetTextureRect(someRenderData.mySpriteSheetRect.myPosition.myX,someRenderData.mySpriteSheetRect.myPosition.myY,someRenderData.mySpriteSheetRect.myWidth,someRenderData.mySpriteSheetRect.myHeight);
	myHGESprites[someRenderData.mySpriteID]->SetBlendMode(someRenderData.myBlendMode);
	myHGESprites[someRenderData.mySpriteID]->SetHotSpot(static_cast<float>(someRenderData.myOrgin.myX),static_cast<float>(someRenderData.myOrgin.myY));
	myHGESprites[someRenderData.mySpriteID]->SetZ(someRenderData.myLayer);
	myHGESprites[someRenderData.mySpriteID]->SetColor(someRenderData.myColor);

	double renderZ = myZ;


	Vector2<double> graphicPosition = someRenderData.myPosition;

	if(someRenderData.myIsUI == false)
	{
		graphicPosition -= aCameraPos;
		graphicPosition.x = graphicPosition.x/renderZ;
		graphicPosition.y = graphicPosition.y/renderZ;
	}
	else
	{
		renderZ = 1.f;
	}

	myHGESprites[someRenderData.mySpriteID]->RenderEx(static_cast<float>(graphicPosition.myX),static_cast<float>(graphicPosition.myY),someRenderData.myRotation,someRenderData.myXScale/static_cast<float>(renderZ),someRenderData.myYScale/static_cast<float>(renderZ));
}
	

void Renderer::RenderMesh(const MeshRenderData& someRenderData,const Vector2<double>& aCameraPos)
{
	double renderZ = myZ;
	if(someRenderData.myIsUI == true)
	{
		renderZ = 1.f;
	}
	Vector2<double> playerPos = (Vector2<double>(myWindowWidth/2.f,myWindowHeight/2.f));
	Vector2<double> midScreenPos = playerPos*renderZ;
	Vector2<double> cameraPos = aCameraPos;
	Vector2<double> graphicPosition;

	float baseHeight = someRenderData.myBaseHeight;
	float topHeight = someRenderData.myTopHeight;

	double skewFactor = 0.01f;

	double topSkew = (topHeight*skewFactor)/renderZ;
	double baseSkew = (baseHeight*skewFactor)/renderZ;

	float aLayerToSetTo = someRenderData.myLayer;

	Vector2<double> dimensions = (someRenderData.myDimensions)/renderZ;

	switch(someRenderData.mySide)
	{
	case W_NORTH:
		{
			graphicPosition = (someRenderData.myPosition - cameraPos)/renderZ;

			aLayerToSetTo += static_cast<float>(((midScreenPos-(someRenderData.myPosition+Vector2<double>(dimensions.x/2,0) - cameraPos)).Length2()-topHeight)/100000000);
			//aLayerToSetTo += static_cast<float>(((playerPos-(someRenderData.myPosition+Vector2<double>(dimensions.x/2,dimensions.y/10) - cameraPos)).Length2()-topHeight)/100000000);

			myMeshCorners[0] = Vector2<double>((graphicPosition.x)+(graphicPosition.x-playerPos.x)*topSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*topSkew);
			myMeshCorners[1] = Vector2<double>((graphicPosition.x+dimensions.x)+(graphicPosition.x+dimensions.x-playerPos.x)*topSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*topSkew);

			myMeshCorners[2] = Vector2<double>(graphicPosition.x+(graphicPosition.x-playerPos.x)*baseSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*baseSkew);
			myMeshCorners[3] = Vector2<double>((graphicPosition.x+dimensions.x)+(graphicPosition.x+dimensions.x-playerPos.x)*baseSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*baseSkew);

			break;
		}
	case W_SOUTH:
		{
			graphicPosition = (Vector2<double>(someRenderData.myPosition.x,someRenderData.myPosition.y+someRenderData.myDimensions.y) - cameraPos)/renderZ;

			aLayerToSetTo += static_cast<float>(((midScreenPos-(someRenderData.myPosition+Vector2<double>(dimensions.x/2,dimensions.y) - cameraPos)).Length2()-topHeight)/100000000);
			//aLayerToSetTo += static_cast<float>(((playerPos-(someRenderData.myPosition+Vector2<double>(dimensions.x/2,dimensions.y-dimensions.y/10) - cameraPos)).Length2()-topHeight)/100000000);

			myMeshCorners[0] = Vector2<double>((graphicPosition.x)+(graphicPosition.x-playerPos.x)*topSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*topSkew);
			myMeshCorners[1] = Vector2<double>((graphicPosition.x+dimensions.x)+(graphicPosition.x+dimensions.x-playerPos.x)*topSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*topSkew);

			myMeshCorners[2] = Vector2<double>(graphicPosition.x+(graphicPosition.x-playerPos.x)*baseSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*baseSkew);
			myMeshCorners[3] = Vector2<double>((graphicPosition.x+dimensions.x)+(graphicPosition.x+dimensions.x-playerPos.x)*baseSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*baseSkew);
			break;
		}
	case W_WEST:
		{
			graphicPosition = (someRenderData.myPosition - cameraPos)/myZ;

			aLayerToSetTo += static_cast<float>(((midScreenPos-(someRenderData.myPosition+Vector2<double>(0,dimensions.y/2) - cameraPos)).Length2()-topHeight)/100000000);
			//aLayerToSetTo += static_cast<float>(((playerPos-(someRenderData.myPosition+Vector2<double>(dimensions.x/10,dimensions.y/2) - cameraPos)).Length2()-topHeight)/100000000);

			myMeshCorners[0] = Vector2<double>((graphicPosition.x)+(graphicPosition.x-playerPos.x)*topSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*topSkew);
			myMeshCorners[1] = Vector2<double>((graphicPosition.x)+(graphicPosition.x-playerPos.x)*topSkew,(graphicPosition.y+dimensions.y)+(graphicPosition.y+dimensions.y-playerPos.y)*topSkew);

			myMeshCorners[2] = Vector2<double>(graphicPosition.x+(graphicPosition.x-playerPos.x)*baseSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*baseSkew);
			myMeshCorners[3] = Vector2<double>(graphicPosition.x+(graphicPosition.x-playerPos.x)*baseSkew,(graphicPosition.y+dimensions.y)+(graphicPosition.y+dimensions.y-playerPos.y)*baseSkew);

			break;
		}
	case W_EAST:
		{
			graphicPosition = (Vector2<double>(someRenderData.myPosition.x+someRenderData.myDimensions.x,someRenderData.myPosition.y) - cameraPos)/renderZ;

			aLayerToSetTo += static_cast<float>(((midScreenPos-(someRenderData.myPosition+Vector2<double>(dimensions.x,dimensions.y/2) - cameraPos)).Length2()-topHeight)/100000000);
			//aLayerToSetTo += static_cast<float>(((playerPos-(someRenderData.myPosition+Vector2<double>(dimensions.x-dimensions.x/10,dimensions.y/2) - cameraPos)).Length2()-topHeight)/100000000);

			myMeshCorners[0] = Vector2<double>((graphicPosition.x)+(graphicPosition.x-playerPos.x)*topSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*topSkew);
			myMeshCorners[1] = Vector2<double>((graphicPosition.x)+(graphicPosition.x-playerPos.x)*topSkew,(graphicPosition.y+dimensions.y)+(graphicPosition.y+dimensions.y-playerPos.y)*topSkew);

			myMeshCorners[2] = Vector2<double>(graphicPosition.x+(graphicPosition.x-playerPos.x)*baseSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*baseSkew);
			myMeshCorners[3] = Vector2<double>(graphicPosition.x+(graphicPosition.x-playerPos.x)*baseSkew,(graphicPosition.y+dimensions.y)+(graphicPosition.y+dimensions.y-playerPos.y)*baseSkew);
			break;
		}
	case W_ROOF:
		{
			graphicPosition = (someRenderData.myPosition - cameraPos)/renderZ;

			aLayerToSetTo += static_cast<float>(((midScreenPos-(someRenderData.myPosition + (dimensions/2) - cameraPos)).Length2()*0.9f-topHeight-50000.f)/100000000);

			myMeshCorners[0] = Vector2<double>((graphicPosition.x)+(graphicPosition.x-playerPos.x)*topSkew,(graphicPosition.y)+(graphicPosition.y-playerPos.y)*topSkew);
			myMeshCorners[1] = Vector2<double>((graphicPosition.x+dimensions.x)+(graphicPosition.x+dimensions.x-playerPos.x)*topSkew,(graphicPosition.y)+(graphicPosition.y-playerPos.y)*topSkew);
			myMeshCorners[2] = Vector2<double>((graphicPosition.x)+(graphicPosition.x-playerPos.x)*topSkew,(graphicPosition.y+dimensions.y)+(graphicPosition.y+dimensions.y-playerPos.y)*topSkew);
			myMeshCorners[3] = Vector2<double>((graphicPosition.x+dimensions.x)+(graphicPosition.x+dimensions.x-playerPos.x)*topSkew,(graphicPosition.y+dimensions.y)+(graphicPosition.y+dimensions.y-playerPos.y)*topSkew);
			break;
		}
	case W_WALL:
		{
			graphicPosition = (someRenderData.myPosition - cameraPos)/renderZ;

			aLayerToSetTo += static_cast<float>(((midScreenPos-(someRenderData.myPosition+Vector2<double>(dimensions.x/2,dimensions.y/2) - cameraPos)).Length2()-topHeight)/100000000);

			myMeshCorners[0] = Vector2<double>((graphicPosition.x)+(graphicPosition.x-playerPos.x)*topSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*topSkew);
			myMeshCorners[1] = Vector2<double>((graphicPosition.x+dimensions.x)+(graphicPosition.x+dimensions.x-playerPos.x)*topSkew,(graphicPosition.y+dimensions.y)+(graphicPosition.y+dimensions.y-playerPos.y)*topSkew);

			myMeshCorners[2] = Vector2<double>(graphicPosition.x+(graphicPosition.x-playerPos.x)*baseSkew,graphicPosition.y+(graphicPosition.y-playerPos.y)*baseSkew);
			myMeshCorners[3] = Vector2<double>((graphicPosition.x+dimensions.x)+(graphicPosition.x+dimensions.x-playerPos.x)*baseSkew,(graphicPosition.y+dimensions.y)+(graphicPosition.y+dimensions.y-playerPos.y)*baseSkew);
			break;
		}
	}


	int numCols = myDistortionMeshes[someRenderData.myMeshID]->GetCols();
	int numRows = myDistortionMeshes[someRenderData.myMeshID]->GetRows();

	Vector2<double> AtoB = myMeshCorners[TOP_RIGHT_CORNER] - myMeshCorners[TOP_LEFT_CORNER];
	double AtoBCell = AtoB.Length()/(numCols-1);
	AtoB.Normalize();

	Vector2<double> AtoC = (myMeshCorners[BOTTOM_LEFT_CORNER] - myMeshCorners[TOP_LEFT_CORNER]);
	double AtoCCell = AtoC.Length()/(numRows-1);
	AtoC.Normalize();

	Vector2<double> BtoD = (myMeshCorners[BOTTOM_RIGHT_CORNER] - myMeshCorners[TOP_RIGHT_CORNER]);
	double BtoDCell = BtoD.Length()/(numRows-1);
	BtoD.Normalize();

	Vector2<double> CtoD = (myMeshCorners[BOTTOM_RIGHT_CORNER] - myMeshCorners[BOTTOM_LEFT_CORNER]);
	double CtoDCell = CtoD.Length()/(numCols-1);
	CtoD.Normalize();

	Vector2<double> xDir;
	double xCell;
	Vector2<double> yDir;
	double yCell;
	for( int curRow = 0; curRow < numRows; ++curRow)
	{
		xDir = (myMeshCorners[TOP_RIGHT_CORNER] + (BtoD * (BtoDCell * curRow))) - (myMeshCorners[TOP_LEFT_CORNER] +(AtoC * (AtoCCell * curRow)));
		xCell = xDir.Length()/static_cast<double>(numCols-1);
		xDir.Normalize();

		for( int curCol = 0; curCol < numCols; ++curCol)
		{
			yDir =  (myMeshCorners[BOTTOM_LEFT_CORNER] + (xDir*(xCell*curCol))) - (myMeshCorners[TOP_LEFT_CORNER] + (xDir*(xCell*curCol)));
			yCell = yDir.Length()/static_cast<double>(numRows-1);
			yDir.Normalize();

			Vector2<double> offset = (yDir*yCell*static_cast<double>(curRow)) + (xDir*xCell*static_cast<double>(curCol));

			myDistortionMeshes[someRenderData.myMeshID]->SetDisplacement(curCol,curRow,static_cast<float>(offset.x),static_cast<float>(offset.y),HGEDISP_TOPLEFT);
			myDistortionMeshes[someRenderData.myMeshID]->SetZ(curCol,curRow,aLayerToSetTo);
			myDistortionMeshes[someRenderData.myMeshID]->SetColor(curCol,curRow,someRenderData.myColor);
		}
	}

	myDistortionMeshes[someRenderData.myMeshID]->Render(static_cast<float>(myMeshCorners[TOP_LEFT_CORNER].x),static_cast<float>(myMeshCorners[TOP_LEFT_CORNER].y));
}

void Renderer::RenderFont(const FontRenderData& someRenderData)
{

	myFonts[someRenderData.myFontId]->SetColor(someRenderData.myColor);
	myFonts[someRenderData.myFontId]->SetRotation(someRenderData.myRotation);
	myFonts[someRenderData.myFontId]->SetScale(someRenderData.myScale);
	myFonts[someRenderData.myFontId]->SetZ(someRenderData.myLayer);

	myFonts[someRenderData.myFontId]->printfb(static_cast<float>(someRenderData.myPosition.x),static_cast<float>(someRenderData.myPosition.y),someRenderData.myBoxWidth,someRenderData.myBoxHeight,someRenderData.myAlignment,someRenderData.myText.c_str());
}

bool Renderer::TextureIsLoaded(const std::string aFilePath, const std::string& aTextureId)
{
	for(int i = 0; i < myLoadedFiles.Count(); ++i)
	{
		if( myLoadedFiles[i] == aFilePath)
		{
			return true;
		}
	}	
	return TextureIsLoaded(aTextureId);
}
bool Renderer::TextureIsLoaded(const std::string aTextureId)
{
	for(int i = 0; i < myTextureIds.Count(); ++i)
	{
		if(myTextureIds[i] == aTextureId)
		{
			return true;
		}
	}
	return false;
}
bool Renderer::FontIsLoaded(const std::string aFontPath)
{
	for(int i = 0; i < myFonts.Count(); ++i)
	{
		if( myFontPaths[i] == aFontPath)
		{
			return true;
		}
	}
	return false;
}

HTEXTURE Renderer::GetLoadedTexture(const std::string& aFilePath, const std::string& aTextureId)
{
	for(int i = 0; i < myLoadedFiles.Count(); ++i)
	{
		if( myLoadedFiles[i] == aFilePath)
		{
			return myTextures[i];
		}
	}
	for(int i = 0; i < myTextureIds.Count(); ++i)
	{
		if( myTextureIds[i] == aTextureId)
		{
			return myTextures[i];
		}
	}
	return NULL;
}

void Renderer::AddHGESprite(const std::string& aFilePath, const std::string& aTextureId)
{
	myTextures.Add(myHGE->Texture_Load(aFilePath.c_str()));
	myLoadedFiles.Add(aFilePath);
	myTextureIds.Add(aTextureId);


	HTEXTURE texture	=	myTextures.GetLast();
	float height		=	TO_FLOAT(myHGE->Texture_GetHeight(texture));
	float width			=	TO_FLOAT(myHGE->Texture_GetWidth(texture));

	//myHGESprites.Add(new hgeSprite(texture,0,0,width,height));

	myHGESprites[myTextureIds.Count()-1] = new hgeSprite(texture,0,0,width,height);
}

void Renderer::AddHGEDistortionMesh(const std::string& aFilePath, const std::string& aTextureId)
{
	myTextures.Add(myHGE->Texture_Load(aFilePath.c_str()));
	myLoadedFiles.Add(aFilePath);
	myTextureIds.Add(aTextureId);

	HTEXTURE texture	=	myTextures.GetLast();
	float height		=	TO_FLOAT(myHGE->Texture_GetHeight(texture));
	float width			=	TO_FLOAT(myHGE->Texture_GetWidth(texture));

	int widthSlicer = 64;
	int heightSlicer = 64;
	while(width/widthSlicer < 2)
	{
		widthSlicer/=2;
	}
	while(height/heightSlicer < 2)
	{
		heightSlicer/=2;
	}
	hgeDistortionMesh* newMesh = new hgeDistortionMesh(static_cast<int>(width)/widthSlicer,static_cast<int>(height)/heightSlicer);
	newMesh->SetTexture(texture);
	newMesh->SetTextureRect(0,0,width,height);

	myDistortionMeshes[myTextureIds.Count()-1] = newMesh;
}

int Renderer::GetSpriteId(const std::string& aTextureId)
{
	for(int i = 0; i < myTextures.Count(); ++i)
	{
		if( myTextureIds[i] == aTextureId )
		{
			return i;
		}
	}
	return -1;
}

int Renderer::GetFontId(const std::string& aFontPath)
{
	for(int i = 0; i < myFontPaths.Count(); ++i)
	{
		if( myFontPaths[i] == aFontPath )
		{
			return i;
		}
	}
	return -1;
}

void Renderer::SortRenderData(GrowingArray<RenderData>& someRenderData)
{
	double totalSum = 0;
	if( someRenderData.Count() == 0 )
	{
		return;
	}
	for(int i = 0; i < someRenderData.Count(); ++i)
	{
		totalSum += someRenderData[i].myLayer;
	}
	double avarge = totalSum/someRenderData.Count();
	GrowingArray<RenderData> leftArray;
	leftArray.Init(32);
	GrowingArray<RenderData> rightArray;
	rightArray.Init(32);
	bool sameLayers = true;

	for(int i = 0; i < someRenderData.Count(); ++i)
	{
		if(someRenderData[i].myLayer > avarge)
		{
			leftArray.Add(someRenderData[i]);
			sameLayers = false;
		}
		else if(someRenderData[i].myLayer < avarge)
		{
			rightArray.Add(someRenderData[i]);
			sameLayers = false;
		}
		else
		{
			if( leftArray.Count() > rightArray.Count() )
			{
				rightArray.Add(someRenderData[i]);
			}
			else
			{
				leftArray.Add(someRenderData[i]);
			}
		}
	}

	if(sameLayers == false)
	{
		SortRenderData(rightArray);
		SortRenderData(leftArray);
	}
	someRenderData.RemoveAll();
	for(int i = 0; i < leftArray.Count(); ++i)
	{
		someRenderData.Add(leftArray[i]);
	}
	for(int i = 0; i < rightArray.Count(); ++i)
	{
		someRenderData.Add(rightArray[i]);
	}
}