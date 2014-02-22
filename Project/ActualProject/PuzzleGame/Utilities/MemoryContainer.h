#ifndef _MEM_CONTAINER_HEADER_
#define _MEM_CONTAINER_HEADER_

#include "GrowingArray.h"
#include "StaticArray.h"


#undef GetObject

template<typename Type, int MaxSize>
class MemoryContainer
{
	
public:
	MemoryContainer();
	virtual ~MemoryContainer();


	Type& operator[](const int& aIndex);
	const Type& operator[](const int& aIndex) const;

	void AddObject(const Type& aType);
	Type& AddEmptyObject();
	void RemoveObject(unsigned int aIndex);
	void RemoveObject(const Type& aType);
	void RemoveObject(Type* aType);
	const Type& GetObject(unsigned int aIndex) const;
	Type& GetObject(unsigned int aIndex);

	int Count();

	void Clear();

private:
	Type* GetAvailableObject();
	void MakeAvailable(Type* aObject);
	
	StaticArray<Type,MaxSize> myObjects;
	GrowingArray<Type*> myObjectPointers;
	GrowingArray<Type*> myAvailableObjects;
};

template<typename Type, int MaxSize>
MemoryContainer<Type,MaxSize>::MemoryContainer()
:	myObjectPointers(MaxSize)
,	myAvailableObjects(MaxSize)
{
	for(int i=0;i<MaxSize;i++)
	{
		myAvailableObjects.Add(&myObjects[i]);
	}
}

template<typename Type, int MaxSize>
MemoryContainer<Type,MaxSize>::~MemoryContainer()
{
}

template<typename Type, int MaxSize>
Type& MemoryContainer<Type,MaxSize>::operator[](const int& aIndex)
{
	return *myObjectPointers[aIndex];
}
template<typename Type, int MaxSize>
const Type& MemoryContainer<Type,MaxSize>::operator[](const int& aIndex) const
{
	return *myObjectPointers[aIndex];
}
template<typename Type, int MaxSize>
void MemoryContainer<Type,MaxSize>::AddObject(const Type& aType)
{
	if(myAvailableObjects.Count() == 0)
	{
		DL_ASSERT("Reached Memorycontainer size limit");
	}
	myObjectPointers.Add(myAvailableObjects.GetLast());
	myAvailableObjects.RemoveLast();
	*(myObjectPointers.GetLast()) = aType;
}

template<typename Type, int MaxSize>
Type& MemoryContainer<Type,MaxSize>::AddEmptyObject()
{
	if(myAvailableObjects.Count() == 0)
	{
		DL_ASSERT("Reached Memorycontainer size limit");
	}
	myObjectPointers.Add(myAvailableObjects.GetLast());
	myAvailableObjects.RemoveLast();
	return *myObjectPointers.GetLast();
}

template<typename Type, int MaxSize>
void MemoryContainer<Type,MaxSize>::RemoveObject(unsigned int aIndex)
{
	MakeAvailable(myObjectPointers[aIndex]);
	myObjectPointers.RemoveCyclicAtIndex(aIndex);
}

template<typename Type, int MaxSize>
void MemoryContainer<Type,MaxSize>::RemoveObject(const Type& aType)
{
	for(int i=0,count=myObjectPointers.Count();i<count;i++)
	{
		if(*myObjectPointers[i] == aType)
		{
			MakeAvailable(myObjectPointers[i]);
			myObjectPointers.RemoveCyclicAtIndex(i);
			return;
		}
	}
}

template<typename Type, int MaxSize>
void MemoryContainer<Type,MaxSize>::RemoveObject(Type* aType)
{
	for(int i=0,count=myObjectPointers.Count();i<count;i++)
	{
		if(myObjectPointers[i] == aType)
		{
			MakeAvailable(myObjectPointers[i]);
			myObjectPointers.RemoveCyclicAtIndex(i);
			return;
		}
	}
}

template<typename Type, int MaxSize>
const Type& MemoryContainer<Type,MaxSize>::GetObject(unsigned int aIndex) const
{
	return *myObjectPointers[aIndex];
}

template<typename Type, int MaxSize>
Type& MemoryContainer<Type,MaxSize>::GetObject(unsigned int aIndex)
{
	return *myObjectPointers[aIndex];
}

template<typename Type, int MaxSize>
int MemoryContainer<Type,MaxSize>::Count()
{
	return myObjectPointers.Count();
}

template<typename Type, int MaxSize>
void MemoryContainer<Type,MaxSize>::Clear()
{
	for(int i=0,count=myObjectPointers.Count();i<count;i++)
	{
		MakeAvailable(myObjectPointers[i]);
	}
	myObjectPointers.RemoveAll();
}

template<typename Type, int MaxSize>
Type* MemoryContainer<Type,MaxSize>::GetAvailableObject()
{
	Type* returnObject = myAvailableObjects.GetLast();
	myAvailableObjects.RemoveLast();
	return returnObject;
}

template<typename Type, int MaxSize>
void MemoryContainer<Type,MaxSize>::MakeAvailable(Type* aObject)
{
	//aObject->~Type();
	aObject->Clear();
	myAvailableObjects.Add(aObject);
}

#endif