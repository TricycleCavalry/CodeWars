#include "BlockFactory.h"

#include "Root.h"

#include "BlockContainer.h"

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
		CreateBlockType(*blockTypeIterator);
		blockTypeIterator = blockTypeIterator->NextSiblingElement();
	}
}

Block* BlockFactory::CreateBlock(XmlElement& anXMLElement)
{
	Block* newBlock = CONTAINERS.myBlockContainer.GetNewBlock();
	
	StringId type = anXMLElement.Attribute("Type");

	//TODO
	//newBlock->Copy(myTypes[type]);
	
	return newBlock;
}

void BlockFactory::CreateBlockType(XmlElement& anXMLElement)
{
	Block* block = CONTAINERS.myBlockContainer.GetNewBlock();

	StringId type = anXMLElement.Attribute("Type");
	myTypes[type] = block;
}

void BlockFactory::CreateBlockAttributes(XmlElement& anXMLElement, Block* aBlock)
{
	XmlElement& attributesList = *anXMLElement.FirstChildElement("Attributes");
	//FACTORIES.myBlockAttributeFactory.CreateAttributeList(attributesList,aBlock->GetAttributes());
}