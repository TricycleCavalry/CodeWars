#ifndef _SPRITE_MANAGER_H_
#define _SPRITE_MANAGER_H_

#include <map>
#include "WrappedMap.h"
#include "SpriteWrapper.h"
#include "HGE.h"

class SpriteManager
{
public:
	SpriteManager(void);
	~SpriteManager(void);

	void SetHGE(HGE *aHGEInstance);
	SpriteWrapper GetSprite(const std::string &aFilePath);
	SpriteWrapper GetSprite(StringId &aSpriteId);

private:
	HGE *myHGE;
	hgeSprite* LoadSprite(const std::string &aFilePath);
	WrappedMap<StringId, hgeSprite*> mySprites;
	
};

#endif