#ifndef BLOCK_ATTRIBUTE_CONTAINER
#define BLOCK_ATTRIBUTE_CONTAINER

#include "MemoryBucket.h"

class BlockAttribute;

class BlockAttributeContainer
{
public:
	BlockAttributeContainer();
	~BlockAttributeContainer();

	template<typename TYPE>
	TYPE* GetNewBlockAttributeType();
	
	template<typename TYPE>
	TYPE* GetNewBlockAttribute();

	void ReturnAttribute(BlockAttribute* anAttribute);
	void ClearAttributeTypes();
	void ClearAttribute();

private:
	MemoryBucket myBlockAttributeTypes;
	MemoryBucket myBlockAttributes;
};

template<typename TYPE>
TYPE* BlockAttributeContainer::GetNewBlockAttributeType()
{
	return myBlockAttributeTypes.GetData<TYPE>();
}
template<typename TYPE>
TYPE* BlockAttributeContainer::GetNewBlockAttribute()
{
	return myBlockAttributes.GetData<TYPE>();
}

#endif