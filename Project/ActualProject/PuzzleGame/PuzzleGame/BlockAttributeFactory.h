#ifndef BLOCK_ATTRIBUTE_FACTORY_HEADER
#define BLOCK_ATTRIBUTE_FACTORY_HEADER

#include "XMLUtil.h"
#include "GrowingArray.h"

class BlockAttribute;

class BlockAttributeFactory
{
public:
	BlockAttributeFactory();
	~BlockAttributeFactory();


	
	void CreateAttributeList(tinyxml2::XMLElement* anAttributeListXML, GrowingArray<BlockAttribute*>& someAttributes);

private:
	BlockAttribute* CreateBlockAttribute(tinyxml2::XMLElement* anBlockAttribute);
	
private:
	BlockAttribute* CreateAttributeFromType(tinyxml2::XMLElement* anAttribute);
	
	BlockAttribute* CreateControllableBlockAttribute(tinyxml2::XMLElement* anAttribute);
	BlockAttribute* CreateBlockingBlockAttribute(tinyxml2::XMLElement* anAttribute);
	BlockAttribute* CreatePushBlockAttribute(tinyxml2::XMLElement* anAttribute);
};

#endif