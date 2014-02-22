#include "BlockAttributeContainer.h"

BlockAttributeContainer::BlockAttributeContainer()
:	myBlockAttributeTypes(1024)
,	myBlockAttributes(1024)
{

}

BlockAttributeContainer::~BlockAttributeContainer()
{

}
	
void BlockAttributeContainer::ReturnAttribute(BlockAttribute* anAttribute)
{

}
void BlockAttributeContainer::ClearAttributeTypes()
{
	myBlockAttributeTypes.Clear();
}
void BlockAttributeContainer::ClearAttribute()
{
	myBlockAttributes.Clear();
}