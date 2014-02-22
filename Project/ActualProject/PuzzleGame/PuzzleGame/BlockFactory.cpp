#include "BlockFactory.h"

#include "Root.h"

#include "BlockContainer.h"
#include "Block.h"

BlockFactory::BlockFactory()
{

}

BlockFactory::~BlockFactory()
{

}

void BlockFactory::LoadTypes(const std::string& aFilepath)
{
	tinyxml2::XMLElement* typeDoc = XMLUTIL::LoadFile(aFilepath);

	tinyxml2::XMLElement* blockTypesList = typeDoc->FirstChildElement();
	tinyxml2::XMLElement* blockTypeIterator = blockTypesList->FirstChildElement();

	while(blockTypeIterator!=NULL)
	{
		CreateBlockType(blockTypeIterator);
		blockTypeIterator = blockTypeIterator->NextSiblingElement();
	}
}

Block* GetBlock(const char* aTypeId)
{
	return NULL;
}

void BlockFactory::CreateBlockType(tinyxml2::XMLElement* anXMLElement)
{
	Block* block = CONTAINERS.myBlockContainer.GetNewBlock();
	myCurrentBlockBlockAttributes.RemoveAll();
	ROOT->GetFactories().myBlockAttributeFactory.CreateAttributeList(anXMLElement,myCurrentBlockBlockAttributes);

	for(int i = 0; i < myCurrentBlockBlockAttributes.Count(); ++i)	
	{
		block->AddAttribute(myCurrentBlockBlockAttributes[i]);
	}
	//block->AddAttributes(myCurrentBlockBlockAttributes);

	StringId type = anXMLElement->Attribute("Id");
	myTypes[type] = block;
}

void BlockFactory::CreateBlockAttributes(tinyxml2::XMLElement* anXMLElement, Block* aBlock)
{
	tinyxml2::XMLElement* attributesList = anXMLElement->FirstChildElement("Attributes");
	//FACTORIES.myBlockAttributeFactory.CreateAttributeList(attributesList,aBlock->GetAttributes());
}