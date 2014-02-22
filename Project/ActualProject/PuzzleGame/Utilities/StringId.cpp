#include "StringId.h"


StringId::StringId(void)
	: myId(-1)
{
}
StringId::StringId(const char* aString)
{
	myId = -1;
	if(aString != NULL)
	{
#ifndef RETAIL
		myString = aString;
#endif
		Hash(aString);
	}
	
}
StringId::StringId(std::string aString)
{
#ifndef RETAIL
	myString = aString;
#endif
	Hash(aString);
}
StringId::StringId(int aId)
	:	myId(aId)

{
}
StringId::StringId(std::string aString,int aId)
	:	myId(aId)
{
#ifndef RETAIL
	myString = aString;
#endif
}
StringId::StringId(const StringId& aStringId)
	:	myId(aStringId.myId)
{
#ifndef RETAIL
	myString = aStringId.myString;
#endif
}
StringId::~StringId(void)
{
}
StringId& StringId::operator = (const StringId& aStringId)
{
	myId = aStringId.myId;
#ifndef RETAIL
	myString = aStringId.myString;
#endif
	return *this;
}
bool StringId::operator == (const StringId& aStringId) const
{
	return(myId == aStringId.myId);
}
bool StringId::operator == (const unsigned int& aId) const
{
	return (myId == aId);
}
bool StringId::operator != (const StringId& aStringId) const
{
	return (myId != aStringId.myId);
}
bool StringId::operator != (const unsigned int& aId) const
{
	return (myId != aId);
}
bool StringId::operator < (const StringId& aStringId) const
{
	return(myId<aStringId.myId);
}
bool StringId::operator > (const StringId& aStringId) const
{
	return (myId>aStringId.myId);
}
const int StringId::GetId() const
{
	return myId;
}

void StringId::Hash(std::string aString)
{
	const char* s = aString.c_str();
	unsigned hash = 0;
    while (*s)
    {
        hash = hash * 101  +  *s++;
    }
	myId = hash;
	if(myId == static_cast<unsigned int>(-1))
	{
		--myId;
	}
	
    
}
