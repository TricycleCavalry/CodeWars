#ifndef BLOCK_FACTORY_HEADER
#define BLOCK_FACTORY_HEADER

#include <map>

#include "XMLUtil.h"
#include "StringId.h"
#include "GrowingArray.h"

class Block;
class BlockAttribute;

class BlockFactory
{
public:
	BlockFactory();
	~BlockFactory();
	
	void LoadTypes(const std::string& aFilepath);

	
	Block* GetBlock(const char* aTypeId);

	Block* GetBlockType(StringId& aId);
private:
	void CreateBlockType(XmlElement* anXMLElement);
	void CreateBlockAttributes(XmlElement* anXMLElement, Block* aBlock);

	std::map<StringId,Block*> myTypes;

	GrowingArray<BlockAttribute*> myCurrentBlockBlockAttributes;
};

#endif