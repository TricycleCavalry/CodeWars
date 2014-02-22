#include "XMLWrapper.h"
#include "Debug.h"
#include "Assert.h"
#include "CommonMacros.h"

XMLWrapper::XMLWrapper(void)
{
	myDocument = NULL;
}

XMLWrapper::~XMLWrapper(void)
{
	SAFE_DELETE(myDocument);
}

void XMLWrapper::OpenFile(const std::string& aFilePath)
{
	File file;
	if(file.Open(aFilePath,F_READ) == false)
	{
		assert(false && "Could not read file");
	}
	file.Close();
	myDocument = new XMLDocument();
	myDocument->LoadFile(aFilePath.c_str());
}

bool XMLWrapper::LoadDocument()
{
	File file;
	std::string filePath(myCurrentElement->GetText());
	if(file.Open(filePath,F_READ) == false)
	{
		assert(false && "Could not read file");
	}
	file.Close();
	myDocument->LoadFile(filePath.c_str());
	if(myDocument)
	{
		return true;
	}
	return false;
}

void XMLWrapper::FindStartElement(const std::string& anElement)
{	
	XMLElement* nextElement = myDocument->FirstChildElement(anElement.c_str());
	if(nextElement)
	{
		myCurrentElement = nextElement;
		return;
	}
	PrintError();
}

void XMLWrapper::FindChildElement(const std::string& anElement)
{
	XMLElement* nextElement = myCurrentElement->FirstChildElement(anElement.c_str());
	if(nextElement)
	{
		myCurrentElement = nextElement;
		return;
	}
	PrintError();
}

bool XMLWrapper::CheckElement(const std::string& anElement)
{
	if(myCurrentElement->FirstChildElement(anElement.c_str()))
	{
		return true;
	}
	return false;
}

bool XMLWrapper::CheckNextElement()
{
	if(myCurrentElement->NextSiblingElement())
	{
		return true;
	}
	return false;
}

bool XMLWrapper::CheckChildElement()
{
	if(myCurrentElement->FirstChildElement())
	{
		return true;
	}
	return false;
}

void XMLWrapper::GoToParentElement()
{
	XMLElement* nextElement = myCurrentElement->Parent()->ToElement();
	if(nextElement)
	{
		myCurrentElement = nextElement;
		return;
	}
	PrintError();
}

void XMLWrapper::GoToChildElement()
{
	XMLElement* nextElement = myCurrentElement->FirstChildElement();
	if(nextElement)
	{
		myCurrentElement = nextElement;
		return;
	}
	PrintError();
}

void XMLWrapper::NextElement()
{
	XMLElement* nextElement = myCurrentElement->NextSiblingElement();
	if(nextElement)
	{
		myCurrentElement = nextElement;
		return;
	}
	PrintError();
}

void XMLWrapper::SearchForElement(const std::string& anElement)
{
	XMLElement* currentElement = myDocument->FirstChildElement();
	std::string elementNameCheck;
	for(;;)
	{
		elementNameCheck = currentElement->Name();
		if(elementNameCheck == anElement)
		{
			myCurrentElement = currentElement;
			return;
		}
		if(currentElement->NoChildren() == true || !currentElement->FirstChildElement())
		{
			XMLElement* nextElement;
			for(;;)
			{
				nextElement = currentElement->NextSiblingElement();
				if(nextElement)
				{
					currentElement = nextElement;
					break;
				}
				else
				{
					nextElement = currentElement->Parent()->ToElement();
					if(nextElement)
					{
						currentElement = nextElement;
					}
					else
					{
						PrintError();
					}
				}
			}
		}
		else
		{
			currentElement = currentElement->FirstChildElement();
		}
	}
	PrintError();
}

tinyxml2::XMLNode* XMLWrapper::GetChildNode(const std::string& anElement)
{
	return reinterpret_cast<tinyxml2::XMLNode*>(myCurrentElement->FirstChildElement(anElement.c_str()));
}

tinyxml2::XMLNode* XMLWrapper::GetNode()
{
	return reinterpret_cast<tinyxml2::XMLNode*>(myCurrentElement);
}

void XMLWrapper::LoadNode(tinyxml2::XMLNode* aNode)
{
	myCurrentElement = reinterpret_cast<XMLElement*>(aNode);
}

int XMLWrapper::GetElementInt(const std::string& anElement)
{
	FindChildElement(anElement);
	int returnInt = GetInt();
	GoToParentElement();
	return returnInt;
}

float XMLWrapper::GetElementFloat(const std::string& anElement)
{
	FindChildElement(anElement);
	float returnFloat = GetFloat();
	GoToParentElement();
	return returnFloat;
}

double XMLWrapper::GetElementDouble(const std::string& anElement)
{
	FindChildElement(anElement);
	double returnDouble = GetDouble();
	GoToParentElement();
	return returnDouble;
}

std::string XMLWrapper::GetElementString(const std::string& anElement)
{
	FindChildElement(anElement);
	std::string returnString = GetString();
	GoToParentElement();
	return returnString;
}

std::string XMLWrapper::GetElementName()
{
	return myCurrentElement->Name();
}

int XMLWrapper::GetInt()
{
	return atoi(myCurrentElement->GetText());
}

float XMLWrapper::GetFloat()
{
	return static_cast<float>(atof(myCurrentElement->GetText()));
}

double XMLWrapper::GetDouble()
{
	return atof(myCurrentElement->GetText());
}

std::string XMLWrapper::GetString()
{
	return myCurrentElement->GetText();
}

void XMLWrapper::PrintError()
{
	//DL_PRINT(myDocument->GetErrorStr1());
	assert(false && "XML ERROR");
}