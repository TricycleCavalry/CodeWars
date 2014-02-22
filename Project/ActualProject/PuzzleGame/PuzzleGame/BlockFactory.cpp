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
	XmlDoc* typeDoc = new XmlDoc();
	typeDoc->LoadFile(aFilepath.c_str());

	XmlElement* blockTypesList = typeDoc->FirstChildElement();
	XmlElement* blockTypeIterator = blockTypesList->FirstChildElement();

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

void BlockFactory::CreateBlockType(XmlElement* anXMLElement)
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

void BlockFactory::CreateBlockAttributes(XmlElement* anXMLElement, Block* aBlock)
{
	XmlElement& attributesList = *anXMLElement->FirstChildElement("Attributes");
	//FACTORIES.myBlockAttributeFactory.CreateAttributeList(attributesList,aBlock->GetAttributes());
}