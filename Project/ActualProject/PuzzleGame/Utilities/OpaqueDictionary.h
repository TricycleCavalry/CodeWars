#ifndef _OPAQUE_DICTIONARY_HEADER_
#define _OPAQUE_DICTIONARY_HEADER_

#include "MemoryBucket.h"
#include "WrappedMap.h"
#include "StringId.h"

class OpaqueDictionary
{
public:
	OpaqueDictionary(unsigned int aSizeInBytes);
	~OpaqueDictionary(void);

	template<typename Type>
	Type& SetDefault(const std::string& aVariableName, const Type& aValue, const bool& aOverrideFlag = true);

	void Clear();

	template<typename Type>
	Type& Get(const std::string& aVariableName);
	template<typename Type>
	const Type& Get(const std::string& aVariableName) const;

	template<typename Type>
	void Set(const std::string& aVariableName,const Type& aValue);
	
	template<typename Type>
	bool Lookup(const std::string& aVariableName, Type*& aPointer);
	bool Lookup(const std::string& aVariableName);


private:
	MemoryBucket myBucket;
	WrappedMap<StringId,char*> myVariables;
};

template<typename Type>
Type& OpaqueDictionary::SetDefault(const std::string& aVariableName, const Type& aValue, const bool& aOverrideFlag)
{
	char* variableLookup;
	Type* variable;
	if(myVariables.FindItem(variableLookup,aVariableName) == false)
	{
		variable = myBucket.GetData<Type>();
		*variable = aValue;
		myVariables.Add(reinterpret_cast<char*>(variable),aVariableName);
	}
	else
	{
		variable = reinterpret_cast<Type*>(variableLookup);		
		if(aOverrideFlag == true)
		{
			*variable = aValue;
		}		
	}
	return *variable;
}

template<typename Type>
Type& OpaqueDictionary::Get(const std::string& aVariableName)
{
#ifdef RETAIL
	return *reinterpret_cast<Type*>(myVariables[aVariableName]);
#else
	char* variable;
	if(myVariables.FindItem(variable,aVariableName) == false)
	{
		DL_ASSERT("Variable: %s was not found in Dictionary",aVariableName.c_str());
	}
	return *reinterpret_cast<Type*>(variable);
#endif
}

template<typename Type>
const Type& OpaqueDictionary::Get(const std::string& aVariableName) const
{
#ifdef RETAIL
	return *reinterpret_cast<Type*>(myVariables[aVariableName]);
#else
	char* variable;
	if(myVariables.FindItem(variable,aVariableName) == false)
	{
		DL_ASSERT("Variable: %s was not found in Dictionary",aVariableName.c_str());
	}
	return *reinterpret_cast<Type*>(variable);
#endif
}
template<typename Type>
void OpaqueDictionary::Set(const std::string& aVariableName,const Type& aValue)
{
	char* variableLookup;
	if(myVariables.FindItem(variableLookup,aVariableName) == true)
	{
		*reinterpret_cast<Type*>(variableLookup) = aValue;
	}
	else
	{
		DL_DEBUG(" %s not set in OpaqueDictionary.",aVariableName.c_str());
	}
}

template<typename Type>
bool OpaqueDictionary::Lookup(const std::string& aVariableName, Type*& aPointer)
{
	char* variableLookup;
	if(myVariables.FindItem(variableLookup,aVariableName) == true)
	{
		if(aPointer == NULL)
		{
			//DL_ASSERT("This is a bit extreme. no?");
		}
		//if(aPointer != NULL)
		{
			aPointer = reinterpret_cast<Type*>(variableLookup);
		}
		return true;
	}
	return false;
}


#endif