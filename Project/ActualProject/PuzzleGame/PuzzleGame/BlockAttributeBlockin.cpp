#include "StdAfx.h"
#include "BlockAttributeBlockin.h"

#include "BlockManager.h"
#include "OpaqueDictionary.h"
#include "Block.h"

BlockAttributeBlockin::BlockAttributeBlockin(void)
:	BlockAttribute(BAT_BLOCK)
{
}

BlockAttributeBlockin::~BlockAttributeBlockin(void)
{
}
void BlockAttributeBlockin::Init()
{
	myOwner->myDictionary.SetDefault(BlockVariables::Blocked,true);
}

void BlockAttributeBlockin::Clear()
{
}
BlockAttribute* BlockAttributeBlockin::SubCopy()
{
	return new BlockAttributeBlockin();
}
