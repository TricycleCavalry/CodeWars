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
void BlockAttribute::Init()
{

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
BlockAttribute* BlockAttribute::Copy()
{
	BlockAttribute* returnAttribute = SubCopy();
	returnAttribute->myType = myType;
	returnAttribute->myOwner = NULL;

	return returnAttribute;
}
