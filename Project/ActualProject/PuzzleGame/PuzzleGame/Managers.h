#ifndef _MANAGERS_H_
#define _MANAGERS_H_

#include  "ControllManager.h"
#include "BlockManager.h"
#include "SpriteManager.h"


class Managers
{
public:
	Managers(void);
	~Managers(void);

public:
	ControllManager myControllManager;
	BlockManager myBlockManager;
	SpriteManager mySpriteManager;


};
#endif