#ifndef _MEM_BUCKET_HEADER_
#define _MEM_BUCKET_HEADER_

#include <map>
#include "assert.h"

class MemBucket
{
public:
	MemBucket(void)	:	myData(NULL), myAddedData(0) {}
	~MemBucket(void){ delete(myData); myData = NULL; }

	void Init(const int& aSizeOfBucket) { myData = reinterpret_cast<char*>(malloc(aSizeOfBucket)); myAddedData = 0; myMaxSize = aSizeOfBucket; }

	template<typename type>
	void SetVariable(const type& aVariable, const std::string& aVariableName);

	template<typename type>
	void AllocateVariable(const std::string& aVariableName);

	template<typename type>
	type& GetVariable(const std::string& aVariableName);

	template<typename type>
	type* GetVariablePointer(const std::string& aVariableName);

private:

	unsigned int myAddedData;
	unsigned int myMaxSize;

	char* myData;

	std::map<std::string,void*> myLookupTable;
};

template<typename type>
void MemBucket::SetVariable(const type& aVariable, const std::string& aVariableName)
{
	if(myAddedData+sizeof(type) > myMaxSize)
	{
		assert(false && "Max Size of MemBucket was reached!");
	}
	type* variableToBePlaced = new (myData+myAddedData) type(aVariable);
	myLookupTable[aVariableName] = reinterpret_cast<void*>(variableToBePlaced);
	myAddedData += sizeof(type);
}

template<typename type>
void MemBucket::AllocateVariable(const std::string& aVariableName)
{
	if(myAddedData+sizeof(type) > myMaxSize)
	{
		assert(false && "Max Size of MemBucket was reached!");
	}
	type* variableToBePlace = new (myData+myAddedData) type();
	myLookupTable[aVariableName] = reinterpret_cast<void*>(variableToBePlace);
	myAddedData += sizeof(type);
}

template<typename type>
type& MemBucket::GetVariable(const std::string& aVariableName)
{
	return *reinterpret_cast<type*>(myLookupTable[aVariableName]);
}

template<typename type>
type* MemBucket::GetVariablePointer(const std::string& aVariableName)
{
	return reinterpret_cast<type*>(myLookupTable[aVariableName]);
}

#endif