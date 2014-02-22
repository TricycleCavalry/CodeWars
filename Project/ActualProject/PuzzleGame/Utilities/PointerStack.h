#ifndef _POINTER_STACK_H_
#define _POINTER_STACK_H_

#include "GrowingArray.h"

template <typename DataType>
class PointerStack
{
public:
	PointerStack(int aSize = 5);
	~PointerStack();

	void Push(const DataType &aValue);

	DataType Pop();
	DataType Top();
	DataType Traverse( const int aDepth );

	int Count();

	bool Find(const DataType &aValue);

	void DeleteAll();

private:
	GrowingArray<DataType> myData;
};

template <typename DataType>
PointerStack<DataType>::PointerStack(int aSize)
{
	myData.Init(aSize);
}
template <typename DataType>
PointerStack<DataType>::~PointerStack()
{
}
template <typename DataType>
void PointerStack<DataType>::Push(const DataType &aValue)
{
	myData.Add(aValue);
}
template <typename DataType>
DataType PointerStack<DataType>::Pop()
{
	DataType value = myData.GetLast();
	myData.DeleteLast();
	return value;
}
template <typename DataType>
DataType PointerStack<DataType>::Top()
{
	return myData.GetLast();
}
template <typename DataType>
DataType PointerStack<DataType>::Traverse( const int aDepth )
{
	return myData[(myData.Count() - 1) - aDepth];
}
template <typename DataType>
int PointerStack<DataType>::Count()
{
	return myData.Count();
}
template <typename DataType>
bool PointerStack<DataType>::Find(const DataType &aValue)
{
	int dataIndex = myData.Find(aValue);
	if(dataIndex < 0)
	{
		return false;
	}
	return true;
}
template <typename DataType>
void PointerStack<DataType>::DeleteAll()
{
	myData.DeleteAll();
}
#endif