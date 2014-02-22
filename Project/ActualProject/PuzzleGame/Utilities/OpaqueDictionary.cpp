#include "OpaqueDictionary.h"


OpaqueDictionary::OpaqueDictionary(unsigned int aSizeInBytes)
:	myBucket(aSizeInBytes)
{
}

OpaqueDictionary::~OpaqueDictionary(void)
{
}

void OpaqueDictionary::Clear()
{
	myVariables.Clear();
	myBucket.Clear();
}

bool OpaqueDictionary::Lookup(const std::string& aVariableName)
{
	return myVariables.HasItem(aVariableName);
}