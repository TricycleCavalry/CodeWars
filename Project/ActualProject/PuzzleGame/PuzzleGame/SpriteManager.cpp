#include "StdAfx.h"
#include "SpriteManager.h"

SpriteManager::SpriteManager(void)
:myHGE(NULL)
{
}

SpriteManager::~SpriteManager(void)
{
	int spriteCount = mySprites.Count();
	for(int index = 0; index < spriteCount; ++index)
	{
		delete mySprites.GetWithIndex(index);
	}
	mySprites.Clear();
}
void SpriteManager::SetHGE(HGE *aHGEInstance)
{
	myHGE = aHGEInstance;
}
SpriteWrapper SpriteManager::GetSprite(const std::string &aFilePath)
{
	StringId spriteId(aFilePath);
	if(mySprites.HasItem(spriteId) == false)
	{
		return SpriteWrapper(LoadSprite(aFilePath));
	}

	return SpriteWrapper(mySprites[spriteId]);
}
SpriteWrapper SpriteManager::GetSprite(StringId &aSpriteId)
{
	SpriteWrapper sprite(mySprites[aSpriteId]);
	return sprite;
}
hgeSprite* SpriteManager::LoadSprite(const std::string &aFilePath)
{
	StringId spriteId(aFilePath);
	if(aFilePath != "")
	{
		HTEXTURE texture = myHGE->Texture_Load(aFilePath.c_str());
		mySprites.Add(new hgeSprite(texture, 0,0, static_cast<float>(myHGE->Texture_GetWidth(texture)), static_cast<float>(myHGE->Texture_GetHeight(texture))), spriteId);
	}
	else
	{
		mySprites.Add(new hgeSprite(0,0,0,32.f,32.f),spriteId);
	}
	return mySprites[spriteId];
}