#include "stdafx.h"
#include "MemoryBucket.h"

#include <stdlib.h>
#include "DL_Debug.h"
#include "CommonMacros.h"

MemoryBucket::MemoryBucket(void)
	:	myData(NULL)
	,	myCurrentSize(0)
	,	myMaxSize(0)
{
}
MemoryBucket::MemoryBucket(int aSize)
	:	myData(static_cast<char*>(malloc(aSize)))
	,	myCurrentSize(0)
	,	myMaxSize(aSize)
{	
}
MemoryBucket::~MemoryBucket(void)
{
	SAFE_FREE(myData);
}

void MemoryBucket::AllocateMemory(int aSize)
{
	if(myData != NULL)
	{
		DL_ASSERT("MemoryBucket already has allocated memory!");
	}
	myData = static_cast<char*>(malloc(aSize));
	myCurrentSize = 0;
	myMaxSize = aSize;
}

void* MemoryBucket::GetMemory() const
{
	return reinterpret_cast<void*>(myData);
}

int MemoryBucket::GetCurrentSize()
{
	return myCurrentSize;
}

const int MemoryBucket::GetMaxSize() const
{
	return myMaxSize;
}
void MemoryBucket::Clear()
{
	myCurrentSize = 0;
}

void MemoryBucket::CopyTo( const MemoryBucket & aBucketToCopyFrom )
{
	memcpy(myData, aBucketToCopyFrom.GetMemory(), aBucketToCopyFrom.GetMaxSize());
	myCurrentSize = aBucketToCopyFrom.myCurrentSize;
	myMaxSize = aBucketToCopyFrom.myMaxSize;
}