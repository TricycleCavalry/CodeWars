#include "BlockFactory.h"

#include "Root.h"

#include "BlockContainer.h"
#include "Block.h"

BlockFactory::BlockFactory()
:	myCurrentBlockBlockAttributes(16)
{

}

BlockFactory::~BlockFactory()
{

}

void BlockFactory::LoadTypes(const std::string& aFilepath)
{
	tinyxml2::XMLElement* typeDoc = XMLUTIL::LoadFile(aFilepath);

	tinyxml2::XMLElement* blockTypeIterator = typeDoc->FirstChildElement();

	while(blockTypeIterator!=NULL)
	{
		CreateBlockType(blockTypeIterator);
		blockTypeIterator = blockTypeIterator->NextSiblingElement();
	}
}

Block* BlockFactory::GetBlock(const char* aTypeId)
{
	return myTypes[aTypeId]->Copy();
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

	Vector4f blockClor = XMLUTIL::GetVector4(anXMLElement->Attribute("Color"),Vector4f(1,1,1,1));
	const char* spriteFilePath = anXMLElement->Attribute("FilePath");
	if(spriteFilePath == NULL)
	{
		spriteFilePath = "";
	}
	block->SetBlockSprite(spriteFilePath,blockClor);

	StringId type = XMLUTIL::GetString(anXMLElement,"Id");
	myTypes[type] = block;
}

void BlockFactory::CreateBlockAttributes(tinyxml2::XMLElement* anXMLElement, Block* aBlock)
{
	tinyxml2::XMLElement* attributesList = anXMLElement->FirstChildElement("Attributes");
	//FACTORIES.myBlockAttributeFactory.CreateAttributeList(attributesList,aBlock->GetAttributes());
}