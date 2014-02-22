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


	
	void CreateAttributeList(XmlElement* anAttributeListXML, GrowingArray<BlockAttribute*>& someAttributes);

private:
	BlockAttribute* CreateBlockAttribute(tinyxml2::XMLElement* anBlockAttribute);
	
private:
	BlockAttribute* CreateAttributeFromType(XmlElement* anAttribute);
	
	BlockAttribute* CreateControllableBlockAttribute(XmlElement* anAttribute);
	BlockAttribute* CreateBlockingBlockAttribute(XmlElement* anAttribute);
};

#endif