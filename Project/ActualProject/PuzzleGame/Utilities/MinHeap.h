#ifndef _MIN_HEAP_H_
#define _MIN_HEAP_H_

#include "GrowingArray.h"
#include <vector>
template <typename TYPE>
class MinHeap
{
public:
	MinHeap(void);
	MinHeap(std::vector<TYPE>& aVector);
	~MinHeap(void);


	void Enqueue(const TYPE& aType);
	TYPE Dequeue();

	int Find(const TYPE& aType);

	bool Empty();

	void RemoveAll();


	//void Swap(const TYPE& aFirstType,const TYPE& aSecondType);

private:
	void Swap(const int& aFirstElement,const int& aSecondElement);

	void MoveDown(const int& aElementToMoveDown);

private:
	GrowingArray<TYPE> myArray;
};
#endif


template <typename TYPE>
MinHeap<TYPE>::MinHeap(void)
:	myArray(20)
{
}
template <typename TYPE>
MinHeap<TYPE>::MinHeap(std::vector<TYPE>& aVector)
:	myArray(2)
{
	for(int i = 0; i < static_cast<int>(aVector.size()); ++i)
	{
		myArray.Add(aVector[i]);
	}
	for(int i = ((myArray.Count()/2) - 1); i >= 0; --i)
	{
		MoveDown(i);
	}
}
template <typename TYPE>
MinHeap<TYPE>::~MinHeap(void)
{
}
template <typename TYPE>
void MinHeap<TYPE>::Enqueue(const TYPE& aType)
{
	myArray.Add(aType);
	int elementPos = myArray.Count()-1;

	while( (elementPos > 0) && (myArray[(elementPos-1)/2]>myArray[elementPos]))
	{
		Swap(elementPos,(elementPos-1)/2);
		elementPos = (elementPos-1)/2;
	}
}
template <typename TYPE>
TYPE MinHeap<TYPE>::Dequeue()
{
	if(myArray.Count() <= 0)
	{
		assert("Dequeue fail");		
	}
	TYPE returnType = myArray[0];
	myArray[0] = myArray.GetLast();
	int elementPos = 0;
	int lastNonLeafElement = (myArray.Count()/2) - 1;

	if(myArray.Count() > 2)
	{
		while( ( elementPos < lastNonLeafElement )
			&&( (myArray[elementPos] > myArray[elementPos*2+1]) || (myArray[elementPos] > myArray[elementPos*2+2]) ) )
		{
			if(myArray[(elementPos*2) + 1] < myArray[(elementPos*2) + 2])
			{
				Swap(elementPos,(elementPos*2) + 1);
				elementPos = (elementPos*2) + 1;
			}
			else
			{
				Swap(elementPos,(elementPos*2) + 2);
				elementPos = (elementPos*2) + 2;
			}
		}
	}
	myArray.RemoveCyclicAtIndex(myArray.Count()-1);
	if(myArray.Count() == 2)
	{
		if(myArray[elementPos] > myArray[elementPos+1])
		{
			Swap(elementPos,(elementPos+1));
		}
	}	
	return returnType;
}
template <typename TYPE>
int MinHeap<TYPE>::Find(const TYPE& aType)
{
	for( int i = 0; i < myArray.Count(); ++i)
	{
		if(myArray[i] == aType)
		{
			return i;
		}
	}
	return -1;
}
template <typename TYPE>
bool MinHeap<TYPE>::Empty()
{
	if(myArray.Count() <= 0)
	{
		return true;
	}
	return false;
}
template <typename TYPE>
void MinHeap<TYPE>::RemoveAll()
{
	myArray.RemoveAll();
}
template <typename TYPE>
void MinHeap<TYPE>::Swap(const int& aFirstElement,const int& aSecondElement)
{
	TYPE tempType = myArray[aFirstElement];

	myArray[aFirstElement]	=	myArray[aSecondElement];
	myArray[aSecondElement]	=	tempType;
}

template <typename TYPE>
void MinHeap<TYPE>::MoveDown(const int& aElementToMoveDown)
{
	int first = aElementToMoveDown;
	int largest = 2 * aElementToMoveDown +1;
	while(largest < myArray.Count())
	{
		if(largest < myArray.Count()-1 && myArray[largest] < myArray[largest+1] )
		{
			++largest;
		}
		if (myArray[first] < myArray[largest])
		{			
			Swap(first,largest);
			first = largest;
			largest = 2*first+1;
		}
		else
		{
			break;
		}
	}
}