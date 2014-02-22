#include "XmlUtil.h"

#include "GrowingArray.h"
#include <string>

using namespace XMLUTIL;

const char* GetAttribute(tinyxml2::XMLElement* anElement, const std::string& anAttributeName)
{
	if(anElement == NULL)
	{
		DL_ASSERT("the element is null");
	}

	const char* attribute = anElement->Attribute(anAttributeName.c_str());
	if(attribute == NULL)
	{
		DL_ASSERT("The attribute %s of the element %s does not exist",anAttributeName.c_str(),anElement->Name());
	}
	return attribute;
}

tinyxml2::XMLElement* XMLUTIL::LoadFile(const std::string& aFilePath)
{
	tinyxml2::XMLDocument* loadedDoc = new tinyxml2::XMLDocument();
	if(loadedDoc->LoadFile(aFilePath.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		DL_ASSERT("Failed to load: %s\nError: %s",aFilePath.c_str(),loadedDoc->GetErrorStr1());
	}
	tinyxml2::XMLElement* rootElement = loadedDoc->RootElement();
	return rootElement;
}

std::string XMLUTIL::GetString(tinyxml2::XMLElement* anElement, const std::string& anAttributeName)
{	
	const char* attribute = GetAttribute(anElement,anAttributeName);
	
	return attribute;
}

Vector2<float> XMLUTIL::GetVector2(tinyxml2::XMLElement* anElement, const std::string& anAttributeName)
{
	const char* attribute = GetAttribute(anElement,anAttributeName);

	return GetVector2(attribute);
}

Vector3<float> XMLUTIL::GetVector3(tinyxml2::XMLElement* anElement, const std::string& anAttributeName)
{
	const char* attribute = GetAttribute(anElement,anAttributeName);

	return GetVector3(attribute);
}

Vector4<float> XMLUTIL::GetVector4(tinyxml2::XMLElement* anElement, const std::string& anAttributeName)
{
	const char* attribute = GetAttribute(anElement,anAttributeName);

	return GetVector4(attribute);
}

float XMLUTIL::GetFloat(tinyxml2::XMLElement* anElement, const std::string& anAttributeName)
{
	const char* attribute = GetAttribute(anElement,anAttributeName);

	return GetFloat(attribute);
}

double XMLUTIL::GetDouble(tinyxml2::XMLElement* anElement, const std::string& anAttributeName)
{
	const char* attribute = GetAttribute(anElement,anAttributeName);

	return atof(attribute);
}

bool XMLUTIL::GetBool(tinyxml2::XMLElement* anElement, const std::string& anAttributeName)
{
	const char* attribute = GetAttribute(anElement,anAttributeName);

	return GetBool(attribute);
}

float XMLUTIL::GetFloat(const char* aFloat, const float& aDefaultValue)
{
	if(aFloat != NULL)
	{
		return static_cast<float>(atof(aFloat));	
	}
	return aDefaultValue;
}

int XMLUTIL::GetInt(const char* anInt, const int& aDefaultValue)
{
	if(anInt != NULL)
	{
		return atoi(anInt);	
	}
	return aDefaultValue;
}
bool XMLUTIL::GetBool(const char* aBool, const bool& aDefaultValue)
{
	if( aBool == NULL)
	{
		return aDefaultValue;
	}
	if( strcmp("false",aBool) == NULL )
	{
		return false;
	}
	else if(  strcmp("true",aBool) == NULL)
	{
		return true;
	}
	return aDefaultValue;
}

Vector2<float> XMLUTIL::GetVector2(const char* aVector, const Vector2<float>& aDefaultValue)
{
	if(aVector == NULL)
	{
		return aDefaultValue;
	}
	Vector2<float> floatVector(0.f,0.f);
	
	GrowingArray<float> floats(2,true);

	std::string vector = aVector;
	vector += ' ';
	//std::string& buffer = vector.c_str();
	short currentChar = 0;
	std::string currentWord = "";


	for(int i = 0; i < 2; ++i)
	{
		do
		{
			currentWord += vector[currentChar];
			currentChar++;
		}while( (vector[currentChar] != ' ' && vector[currentChar] != ',') && vector[currentChar] != EOF );

		floats.Add(static_cast<float>( atof( currentWord.c_str() ) ));
		currentWord = "";
		currentChar++;
	}

	floatVector.myX = floats[0];
	floatVector.myY = floats[1];

	return floatVector;
}

Vector3<float> XMLUTIL::GetVector3(const char* aVector,const Vector3<float>& aDefaultValue)
{
	if(aVector == NULL)
	{
		return aDefaultValue;
	}

	Vector3<float> floatVector(0.f,0.f,0.f);

	GrowingArray<float> floats(4,true);

	std::string vector = aVector;
	vector += ' ';

	short currentChar = 0;
	std::string currentWord = "";

	for(int i=0; i < 3; ++i)
	{
		do
		{
			currentWord += vector[currentChar];
			currentChar++;
		}while( (vector[currentChar] != ' ' && vector[currentChar] != ',') && vector[currentChar] != EOF );

		floats.Add(static_cast<float>( atof( currentWord.c_str() ) ));
		currentWord = "";
		currentChar++;
	}

	floatVector.myX = floats[0];
	floatVector.myY = floats[1];
	floatVector.myZ = floats[2];

	return floatVector;
}
Vector4<float> XMLUTIL::GetVector4(const char* aVector,const Vector4<float>& aDefaultValue)
{
	if(aVector == NULL)
	{
		return aDefaultValue;
	}

	Vector4<float> floatVector(0.f,0.f,0.f,0.f);

	GrowingArray<float> floats(4,true);

	std::string vector = aVector;
	vector += ' ';

	short currentChar = 0;
	std::string currentWord = "";

	for(int i=0; i < 4; ++i)
	{
		do
		{
			currentWord += vector[currentChar];
			currentChar++;
		}while( (vector[currentChar] != ' ' && vector[currentChar] != ',') && vector[currentChar] != EOF );

		floats.Add(static_cast<float>( atof( currentWord.c_str() ) ));
		currentWord = "";
		currentChar++;
	}

	floatVector.myX = floats[0];
	floatVector.myY = floats[1];
	floatVector.myZ = floats[2];
	floatVector.myW = floats[3];

	return floatVector;
}