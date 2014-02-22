#ifndef BLOCK_ATTRIBUTE_CONTAINER
#define BLOCK_ATTRIBUTE_CONTAINER

class BlockAttribute;

class BlockAttributeContainer
{
public:
	BlockAttributeContainer();
	~BlockAttributeContainer();
	
	void ReturnAttribute(BlockAttribute* anAttribute);
};

#endif