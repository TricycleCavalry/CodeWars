#ifndef _STRING_ID_H_
#define _STRING_ID_H_

#include <string>

class StringId
{
public:
	StringId(void);
	StringId(const char* aString);
	StringId(std::string aString);
	StringId(int aId);
	StringId(std::string aString,int aId);
	StringId(const StringId& aStringId);
	~StringId(void);


	StringId& operator = (const StringId& aStringId);
	bool operator == (const StringId& aStringId) const;
	bool operator == (const unsigned int& aId) const;	
	bool operator != (const StringId& aStringId) const;
	bool operator != (const unsigned int& aId) const;
	bool operator < (const StringId& aStringId) const;
	bool operator > (const StringId& aStringId) const;

	const int GetId() const;
#ifndef RETAIL
	const char* c_str() const {return myString.c_str();}
#endif

private:
	void Hash(std::string aString);

private:
#ifndef RETAIL
	std::string myString;
#endif
	unsigned int myId;

};

#endif