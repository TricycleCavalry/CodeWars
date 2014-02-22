#include "BlockAttributeFactory.h"

#include <string>

#include "XMLUtil.h"
#include "GrowingArray.h"

BlockAttributeFactory::BlockAttributeFactory()
{

}

BlockAttributeFactory::~BlockAttributeFactory()
{

}

void BlockAttributeFactory::CreateAttributeList(XmlElement& anAttributeListXML, GrowingArray<BlockAttribute*>& someAttributes)
{
	someAttributes.RemoveAll();
	
	
}
	
BlockAttribute* BlockAttributeFactory::CreateAttributeFromType(XmlElement& anAttributeXml)
{
	BlockAttribute* attribute = NULL;
	
	std::string attributeType = anAttributeXml.Name();
	
	if(attributeType=="Controllable")
	{
		attribute = CreateControllableAttribute(anAttributeXml);
	}
	
	return attribute;
}

BlockAttribute* BlockAttributeFactory::CreateControllableAttribute(XmlElement& anAttributeXml)
{
	//ControllableBlockAttribute* attribute = ROOT->CONTAINERS->BLOCK_ATTRIBUTE->GetNewControllableBlockAttribute();
	
	BlockAttribute* attribute = NULL;
	//init shizzle
	
	return attribute;
}