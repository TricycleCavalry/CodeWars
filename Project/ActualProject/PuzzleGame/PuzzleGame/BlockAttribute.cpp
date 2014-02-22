#include "StdAfx.h"
#include "BlockAttribute.h"

#include "Block.h"

BlockAttribute::BlockAttribute(BlockAttributeType aType)
:myOwner(NULL)	
,myType(aType)
{
}

BlockAttribute::~BlockAttribute(void)
{
}

BlockAttributeType BlockAttribute::GetType()
{
	return myType;
}
void BlockAttribute::SetOwner(Block* aBlock)
{
	myOwner = aBlock;
}

void BlockAttribute::Update(const float anElapsedTime)
{
}
//void BlockAttribute::OnEnter()
//{
//}
//void BlockAttribute::OnExit()
//{
//}
//void BlockAttribute::Clear()
//{
//}
