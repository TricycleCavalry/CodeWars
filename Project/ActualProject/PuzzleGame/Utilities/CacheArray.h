#ifndef _CACHE_ARRAY_HEADER_
#define _CACHE_ARRAY_HEADER_

#include <Assert.h>
#include <Windows.h>
#include "CommonMacros.h"

template<typename Type>
class CacheArray
{
public:
	CacheArray();
	CacheArray(int aSize);
	~CacheArray();

	void Init(int aSize);

	inline void Add(const Type& aType);
	inline void Add(const Type& aType, int aDesiredIndex);
	inline void Push(const Type& aType);
	inline void Clear();

	inline void RemoveOrdered(int aIndex);
	inline void RemoveCyclic(const Type& aType);
	inline void RemoveCyclicAtIndex(int aIndex);

	inline Type& operator[](int anIndex);
	inline const Type& operator[](int anIndex) const;

	inline Type* GetArray() const;

	__forceinline int Count() const;

	__forceinline int MaxCount() const;

private:
	Type* myCache;
	int mySize;
	int myUsedSize;
};

template<typename Type>
CacheArray<Type>::CacheArray()
:	myCache(NULL)
,	mySize(0)
,	myUsedSize(0)
{
}

template<typename Type>
CacheArray<Type>::CacheArray(int aSize)
:	myCache(new Type[aSize])
,	mySize(aSize)
,	myUsedSize(0)
{
}

template<typename Type>
CacheArray<Type>::~CacheArray()
{
	delete[] myCache;
	myCache = NULL;
}

template<typename Type>
void CacheArray<Type>::Init(int aSize)
{
	assert(myCache == NULL && "Cache alreay initialized");
	myCache = new Type[aSize];
	mySize = aSize;
}

template<typename Type>
inline void CacheArray<Type>::Add(const Type& aType)
{
	assert(myCache != NULL && "Uninitialized Cache");
	myUsedSize = MIN(myUsedSize+1,mySize);
	myCache[myUsedSize-1] = aType;
}

template<typename Type>
inline void CacheArray<Type>::Add(const Type& aType, int aDesiredIndex)
{
	assert(myCache != NULL && "Uninitialized Cache");
	(myUsedSize == mySize) ? myCache[aDesiredIndex] = aType : myCache[myUsedSize-1] = aType;
	myUsedSize = MIN(myUsedSize+1,mySize);
}

template<typename Type>
inline void CacheArray<Type>::Push(const Type& aType)
{
	assert(myCache != NULL && "Uninitialized Cache");

	for(int i=myUsedSize-1;i>0;i--)
	{
		myCache[i] = myCache[i-1];
	}
	myCache[0] = aType;
	myUsedSize = MIN(myUsedSize+1,mySize);
}

template<typename Type>
inline void CacheArray<Type>::Clear()
{
	myUsedSize = 0;
}

template<typename Type>
inline void CacheArray<Type>::RemoveOrdered(int aIndex)
{
	assert(myCache != NULL && "Uninitialized Cache");
	assert(anIndex >= 0 && "Index Out of bounds");
	assert(anIndex < myUsedSize && "Index Out of bounds");

	for(int i=aIndex+1;i<myUsedSize;i++)
	{
		myCache[i-1] = myCache[i];
	}
	myUsedSize--;
}

template<typename Type>
inline void CacheArray<Type>::RemoveCyclic(const Type& aType)
{
	assert(myCache != NULL && "Uninitialized Cache");

	for(int i=0;i<myUsedSize;i++)
	{
		if(myCache[i] == aType)
		{

		}
	}
}

template<typename Type>
inline void CacheArray<Type>::RemoveCyclicAtIndex(int aIndex)
{
	assert(myCache != NULL && "Uninitialized Cache");
	assert(aIndex >= 0 && "Index Out of bounds");
	assert(aIndex < myUsedSize && "Index Out of bounds");

	myCache[aIndex] = myCache[myUsedSize-1];
	
}

template<typename Type>
inline Type& CacheArray<Type>::operator[](int anIndex)
{
	assert(myCache != NULL && "Uninitialized Cache");
	assert(anIndex >= 0 && "Index Out of bounds");
	assert(anIndex < myUsedSize && "Index Out of bounds");

	return myCache[anIndex];
}

template<typename Type>
inline const Type& CacheArray<Type>::operator[](int anIndex) const
{
	assert(myCache != NULL && "Uninitialized Cache");
	assert(anIndex >= 0 && "Index Out of bounds");
	assert(anIndex < myUsedSize && "Index Out of bounds");

	return myCache[anIndex];
}

template<typename Type>
inline Type* CacheArray<Type>::GetArray() const
{
	return myCache;
}

template<typename Type>
__forceinline int CacheArray<Type>::Count() const
{
	return myUsedSize;
}

template<typename Type>
__forceinline int CacheArray<Type>::MaxCount() const
{
	return mySize;
}

#endif