#ifndef MAIL_HEADER
#define MAIL_HEADER

#include "memory.h"
#include "MailType.h"
#include "CommonMacros.h"

#define NULL 0

//template<class TYPE>
class Mail
{
public:
	Mail(MailType aMailType)
	:	myMailType(aMailType)
	,	myIsNew(false)
	,	myValue(NULL)
	{
	}

	~Mail()
	{ 
		if(myIsNew == true)
		{	
			SAFE_DELETE(myValue);
		}
		else
		{
			myValue=NULL;
		}
	}

	
	

	template<class TYPE>
	void AddNewValue(const TYPE& aValue);
	template<class TYPE>
	void AddValue(TYPE& aValue);

	template<class TYPE>
	void GetValue(TYPE& aValue);
	template<class TYPE>
	TYPE GetValue(); 
	
	MailType myMailType;

private:
	void* myValue;
	bool myIsNew;
};

template<class TYPE>
void Mail::AddNewValue(const TYPE& aValue)
{
	if(myIsNew == true)
	{
		SAFE_DELETE(myValue);
	}
	myValue = new TYPE(aValue);
	myIsNew = true;
}

template<class TYPE>
void Mail::AddValue(TYPE& aValue)
{
	if(myIsNew == true)
	{
		SAFE_DELETE(myValue);
	}
	myValue = &aValue;
	myIsNew = false;
}

template<class TYPE>
void Mail::GetValue(TYPE& aValue)
{
	memcpy(&aType, myValue, sizeof(TYPE));
}

template<class TYPE>
TYPE Mail::GetValue()
{
	return *reinterpret_cast<TYPE*>(myValue);
}

#endif