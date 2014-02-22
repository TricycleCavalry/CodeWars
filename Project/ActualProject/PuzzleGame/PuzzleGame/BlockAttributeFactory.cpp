#include "BlockAttributeFactory.h"

#include <string>

#include "XMLUtil.h"
#include "GrowingArray.h"
#include "Root.h"

#include "BlockAttributeBlockin.h"
#include "BlockAttributeControllable.h"

BlockAttributeFactory::BlockAttributeFactory()
{

}

BlockAttributeFactory::~BlockAttributeFactory()
{

}

void BlockAttributeFactory::CreateAttributeList(tinyxml2::XMLElement* anAttributeListXML, GrowingArray<BlockAttribute*>& someAttributes)
{
	//someAttributes.RemoveAll();
	tinyxml2::XMLElement* attributes = anAttributeListXML->FirstChildElement();
	tinyxml2::XMLElement* attribute = attributes->FirstChildElement();
	while(attribute != NULL)
	{
		someAttributes.Add(CreateAttributeFromType(attribute));
		attribute = attribute->NextSiblingElement();
	}
	
}
BlockAttribute* BlockAttributeFactory::CreateAttributeFromType(tinyxml2::XMLElement* anAttributeXml)
{
	BlockAttribute* attribute = NULL;
	
	std::string attributeType = anAttributeXml->Name();
	
	if(attributeType == "Controllable")
	{
		attribute = CreateControllableBlockAttribute(anAttributeXml);
	}
	else if( attributeType == "Blocking")
	{
		attribute = CreateBlockingBlockAttribute(anAttributeXml);
	}
	
	return attribute;
}

BlockAttribute* BlockAttributeFactory::CreateControllableBlockAttribute(tinyxml2::XMLElement* anAttributeXml)
{
	//TODO
	//ControllableBlockAttribute* attribute = ROOT->CONTAINERS->BLOCK_ATTRIBUTE->GetNewControllableBlockAttribute();
	BlockAttributeControllable* controllableAttribute = new BlockAttributeControllable();
	
	
	//BlockAttribute* attribute = NULL;
	//init shizzle
	
	return controllableAttribute;
}

BlockAttribute* BlockAttributeFactory::CreateBlockingBlockAttribute(tinyxml2::XMLElement* anAttribute)
{
	BlockAttributeBlockin* blockblockAttribute = new BlockAttributeBlockin();

	return blockblockAttribute;
}