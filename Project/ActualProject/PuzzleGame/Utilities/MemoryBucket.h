#ifndef _MEMORY_BUCKET_H_
#define _MEMORY_BUCKET_H_

#include "DL_Debug.h"

class MemoryBucket
{
public:
	MemoryBucket(void);
	MemoryBucket(int aSize);
	~MemoryBucket(void);

	void AllocateMemory(int aSize);
	
	template<typename TYPE>
	TYPE* GetData();
	template<typename TYPE>
	void* GetRawData();
	template<typename TYPE>
	TYPE* GetData(const int& aMemoryOffset);

	void CopyTo( const MemoryBucket & aBucketToCopyFrom );

	void* GetMemory() const;

	int GetCurrentSize();
	const int GetMaxSize() const;

	void Clear();

private:
	char* myData;
	int myMaxSize;
	int myCurrentSize;
};


template<typename TYPE>
TYPE* MemoryBucket::GetData()
{	
	if( static_cast<int>(myCurrentSize + sizeof(TYPE)) > myMaxSize)
	{
		DL_ASSERT("MemoryBucket Overflow!");
	}
	TYPE* returnData = new(&myData[myCurrentSize])TYPE();
	myCurrentSize += sizeof(TYPE);	
	return returnData;
}
template<typename TYPE>
void* MemoryBucket::GetRawData()
{
	if( static_cast<int>(myCurrentSize + sizeof(TYPE)) > myMaxSize)
	{
		DL_ASSERT("MemoryBucket Overflow!");
	}
	myCurrentSize += sizeof(TYPE);
	return reinterpret_cast<void*>(&myData[myCurrentSize - sizeof(TYPE)]);
}
template<typename TYPE>
TYPE* MemoryBucket::GetData(const int& aMemoryOffset)
{
	if(aMemoryOffset > myMaxSize || aMemoryOffset > myCurrentSize)
	{
		DL_ASSERT("MemoryBucket trying to access data outside of MemoryBucket!");
	}
	char* memoryPosition = myData + aMemoryOffset;	
	return reinterpret_cast<TYPE*>(memoryPosition);
}

#endif 