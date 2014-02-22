#ifndef BLOCK_FACTORY_HEADER
#define BLOCK_FACTORY_HEADER

#include <map>

#include "XMLUtil.h"
#include "StringId.h"

class Block;

class BlockFactory
{
public:
	BlockFactory();
	~BlockFactory();
	
	void LoadTypes(const std::string& aFilepath);

	Block* CreateBlock(XmlElement& anXMLElement);

	Block* GetBlockType(StringId& aId);
private:
	void CreateBlockType(XmlElement& anXMLElement);
	void CreateBlockAttributes(XmlElement& anXMLElement, Block* aBlock);

	std::map<StringId,Block*> myTypes;
};

#endif