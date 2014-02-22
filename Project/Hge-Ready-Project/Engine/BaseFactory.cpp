#include "BaseFactory.h"
#include "StaticArray.h"
#include "tinyxml2.h"
#include "Debug.h"

#include "hge.h"

BaseFactory::BaseFactory(void)
{
}

BaseFactory::~BaseFactory(void)
{
}

Rect BaseFactory::GetRectangle(const char* aRectangle)
{
	
	StaticArray<float,4> tempObjectRect;

	std::string rectangle = aRectangle;
	rectangle += ' ';

	short currentChar = 0;
	std::string currentWord = "";
	for(int i = 0; i < 4; ++i)
	{	
		do
		{
			currentWord += rectangle[currentChar];
			currentChar++;
		}while(rectangle[currentChar] != ' ');
		tempObjectRect[i] = static_cast<float>(atof(currentWord.c_str()));
		currentChar++;
		currentWord = "";
	}
	return Rect(Vector2<float>(tempObjectRect[0],tempObjectRect[1]),tempObjectRect[2],tempObjectRect[3]);

}
Vector2<float> BaseFactory::GetVector(const char* aVector)
{
	if(aVector == NULL)
	{
		return Vector2<float>(0,0);
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
		}while(vector[currentChar] != ' ');

		floats.Add(static_cast<float>( atof( currentWord.c_str() ) ));
		currentWord = "";
		currentChar++;
	}

	floatVector.myX = floats[0];
	floatVector.myY = floats[1];

	return floatVector;
}

float BaseFactory::GetFloat(const char* aFloat)
{
	if(aFloat != NULL)
	{
		return static_cast<float>(atof(aFloat));	
	}
	return 0;
}

int BaseFactory::GetInt(const char* anInt)
{
	if(anInt != NULL)
	{
		return atoi(anInt);	
	}
	return 0;
}
bool BaseFactory::GetBool(const char* aBool)
{
	if( aBool == NULL)
	{
		return false;
	}
	if( strcmp("false",aBool) == NULL )
	{
		return false;
	}
	else if(  strcmp("true",aBool) == NULL)
	{
		return true;
	}
	DL_ASSERT("Bool was not found, you may have miss-spelled true/false");
	return false;
}
DWORD BaseFactory::GetColor(const char* aColor)
{
	if(aColor == NULL)
	{
		return ARGB(255,255,255,255);
	}
	int colorARGB[4];

	std::string colorString = aColor;
	colorString += ' ';
	short currentChar = 0;
	std::string currentWord = "";
	for(int i = 0; i < 4; ++i)
	{
		do
		{
			currentWord += colorString[currentChar];
			currentChar++;
		}while(colorString[currentChar] != ' ');

		
		colorARGB[i] = atoi( currentWord.c_str() );
		currentWord = "";
		currentChar++;
	}


	return ARGB(colorARGB[0],colorARGB[1],colorARGB[2],colorARGB[3]);

}

int BaseFactory::FindElement(const GrowingArray<std::string>& anArray,const std::string& anIdToFind)
{
	for(int i = 0; i < anArray.Count(); ++i)
	{
		if(  anArray[i] == anIdToFind)
		{
			return i;
		}
	}
	DL_CRITICAL("Element was not found: %s",anIdToFind.c_str());
	DL_ASSERT("Element was not found");
	return -1;
}

OriginCorners BaseFactory::GetCorner(std::string aString)
{
	if(aString == "TOP_LEFT")
	{
		return TOP_LEFT;
	}
	if(aString == "TOP_RIGHT")
	{
		return TOP_RIGHT;
	}
	if(aString == "DOWN_LEFT")
	{
		return DOWN_LEFT;
	}
	if(aString == "DOWN_RIGHT")
	{
		return DOWN_RIGHT;
	}

	if(aString == "CENTER_LEFT")
	{
		return CENTER_LEFT;
	}
	if(aString == "CENTER_RIGHT")
	{
		return CENTER_RIGHT;
	}
	if(aString == "CENTER_TOP")
	{
		return CENTER_TOP;
	}
	if(aString == "CENTER_DOWN")
	{
		return CENTER_DOWN;
	}
	DL_CRITICAL("Fail on HUD Corner: %s", aString.c_str());
	return CENTER_DOWN;
}
Vector2<float> BaseFactory::GetPositionDependentOnCorner(const OriginCorners& aCorner,const Vector2<float>& aPosition,const Vector2<int>& someWindowDimensions)
{
	Vector2<float> returnVector = aPosition;
	switch(aCorner)
	{
	case TOP_LEFT:
		break;
	case DOWN_LEFT:
		returnVector.myY = someWindowDimensions.y - aPosition.y;
		break;
	case TOP_RIGHT:
		returnVector.myX = someWindowDimensions.x - aPosition.x;
		break;	
	case DOWN_RIGHT:
		returnVector = Vector2<float>(static_cast<float>(someWindowDimensions.x),static_cast<float>(someWindowDimensions.y)) - aPosition;
		break;
	case CENTER_LEFT:
		returnVector = Vector2<float>(0.f,static_cast<float>(someWindowDimensions.y)/2);
		break;
	case CENTER_RIGHT:
		returnVector = Vector2<float>(static_cast<float>(someWindowDimensions.x),static_cast<float>(someWindowDimensions.y)/2) ;
		break;
	case CENTER_TOP:
		returnVector = Vector2<float>(static_cast<float>(someWindowDimensions.x)/2,0.f) + aPosition;
		break;
	case CENTER_DOWN:
		returnVector = Vector2<float>(static_cast<float>(someWindowDimensions.x)/2,static_cast<float>(someWindowDimensions.y))  - aPosition;
		break;
	}
	return returnVector;
}