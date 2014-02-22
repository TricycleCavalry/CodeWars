#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "hge.h"
#include "hgeFont.h"
#include "GrowingArray.h"
#include "StaticArray.h"
#include "RenderData.h"
#include "Vector2.h"

#include <map>

#define WHITE 4294967295

class hgeSprite;
class Sprite;
class DistortionMesh;
class Font;
class hgeDistortionMesh;
class Camera;




class Renderer
{
public:
	Renderer(HGE* aHGE);
	~Renderer(void);

	bool Init();
	bool Render();

	void AddTexture(const std::string& aFilePath,const std::string& aTextureId);
	void AddMeshTexture(const std::string& aFilePath,const std::string& aTextureId);

	Sprite*			AddSprite(const std::string&  aTextureId,const Rect& aRect, const Vector2<float> aOrgin, const int aBlendMode = BLEND_DEFAULT, const float& aRotation = 0.0f);
	DistortionMesh* AddMesh(const std::string&  aTextureId,const Rect& aRect, const int aBlendMode = BLEND_DEFAULT);
	Font*			AddFont(const std::string aFilePath,const DWORD& aColor);
	void AddToRenderQueue(const Sprite& aSprite,const float aXPos,const float aYPos,const float aLayer = 1.0f,const float aRotation = 0, const float aXScale = 1, const float aYScale = 1, const DWORD& aColor = WHITE, bool aIsUIFlag = false);
	void AddToRenderQueue(const DistortionMesh& aMesh, const float aXPos, const float aYPos, const float aLayer, const float& aBaseHeight, const float& aTopHeight, const WallSides& aSide, const float& aWidth, const float& aHeight, const DWORD& aColor = WHITE, bool aIsUIFlag = false);
	void AddToRenderQueue(const Font& aFont,const float& aXPos,const float& aYPos, const float& aLayer,const float& aRotation, const float& aScale,const DWORD& aColor,const int& anAlignment, const std::string& aText,const float& aBoxWidth = 2048.f,const float& aBoxHeight = 2048.f);
	void CleanQueue();
	void SwitchQueues();


	hgeFont* GetFont(const int& aId);

	void SetCameraPosition(Vector2<float>* aCameraPosition);
	void SetCamera(Camera* aCamera);
	void SetWindowHeightPointers(Vector2<float*> someWindowDimensions);
	void ChangeZ(const double& aZ);
	void SetZ(const double& aZ);

	void SetHGE(HGE* aHGE);

	//static void RenderDebugLine(const Vector2<float>& aFirstPoint,const Vector2<float>& aSecondPoint,const DWORD& aColor);
	
private:

	void SortRenderData(GrowingArray<RenderData>& someRenderData);
	HGE* myHGE;
	Vector2<float>* myCameraPosition;
	Camera*	myCamera;
	Vector2<float*> myWindowDimensions;
	Vector2<float> myOriginalDimensions;
	double myZ;
	
	int myCurrentRenderingQueue;
	int myCurrentBuildingQueue;
	StaticArray<GrowingArray<RenderData>,2> myRenderingQueues;
	StaticArray<GrowingArray<MeshRenderData>,2> myMeshRenderingQueues;
	StaticArray<GrowingArray<FontRenderData>,2> myFontRenderingQueues;

	//GrowingArray<hgeSprite*>			myHGESprites;
	//GrowingArray<hgeDistortionMesh*>	myDistortionMeshes;
	GrowingArray<std::string>			myLoadedFiles;
	GrowingArray<HTEXTURE>				myTextures;
	GrowingArray<std::string>			myTextureIds;
	GrowingArray<std::string>			myFontPaths;

	StaticArray<Vector2<double>,4>		myMeshCorners;

	std::map<int, hgeSprite*> myHGESprites;
	std::map<int, hgeDistortionMesh*> myDistortionMeshes;
	GrowingArray<hgeFont*> myFonts;

	int myWindowWidth;
	int myWindowHeight;


	void RenderSprite(const RenderData& someRenderData,const Vector2<double>& aCameraPos);
	void RenderMesh(const MeshRenderData& someRenderData,const Vector2<double>& aCameraPos);
	void RenderFont(const FontRenderData& someRenderData);
	bool TextureIsLoaded(const std::string aFilePath, const std::string& aTextureId);
	bool TextureIsLoaded(const std::string aTextureId);
	bool FontIsLoaded(const std::string aFontPath);
	HTEXTURE GetLoadedTexture(const std::string& aFilePath, const std::string& aTextureId);
	void AddHGESprite(const std::string& aFilePath, const std::string& aTextureId);
	void AddHGEDistortionMesh(const std::string& aFilePath, const std::string& aTextureId);
	int GetSpriteId(const std::string& aFilePath);
	int GetFontId(const std::string& aFontPath);
	

};

#endif