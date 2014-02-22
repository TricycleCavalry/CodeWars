#include "StdAfx.h"
#include "BlockAttributeBlockin.h"

#include "BlockManager.h"

BlockAttributeBlockin::BlockAttributeBlockin(void)
:	BlockAttribute(BAT_BLOCK)
{
}

BlockAttributeBlockin::~BlockAttributeBlockin(void)
{
}
void BlockAttributeBlockin::Init()
{
	
}

void BlockAttributeBlockin::Clear()
{
}
BlockAttribute* BlockAttributeBlockin::SubCopy()
{
	return new BlockAttributeBlockin();
}
