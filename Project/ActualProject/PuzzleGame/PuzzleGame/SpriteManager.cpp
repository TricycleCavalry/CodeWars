#include "StdAfx.h"
#include "SpriteManager.h"

SpriteManager::SpriteManager(HGE &aHGE)
:myHGE(aHGE)
{
}

SpriteManager::~SpriteManager(void)
{
	
		
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
	HTEXTURE texture = myHGE.Texture_Load(aFilePath.c_str());
	mySprites.Add(new hgeSprite(texture, 0,0, static_cast<float>(myHGE.Texture_GetWidth(texture)), static_cast<float>(myHGE.Texture_GetHeight(texture))), spriteId);
	return mySprites[spriteId];
}