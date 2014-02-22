#ifndef _STACK_H_
#define _STACK_H_

#include "GrowingArray.h"

template <typename DataType>
class Stack
{
public:
	Stack(int aSize = 5);
	~Stack();

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
Stack<DataType>::Stack(int aSize)
{
	myData.Init(aSize);
}
template <typename DataType>
Stack<DataType>::~Stack()
{
}
template <typename DataType>
void Stack<DataType>::Push(const DataType &aValue)
{
	myData.Add(aValue);
}
template <typename DataType>
DataType Stack<DataType>::Pop()
{
	DataType value = myData.GetLast();
	//myData.DeleteLast();
	myData.RemoveLast();
	return value;
}
template <typename DataType>
DataType Stack<DataType>::Top()
{
	return myData.GetLast();
}
template <typename DataType>
DataType Stack<DataType>::Traverse( const int aDepth )
{
	return myData[(myData.Count() - 1) - aDepth];
}
template <typename DataType>
int Stack<DataType>::Count()
{
	return myData.Count();
}
template <typename DataType>
bool Stack<DataType>::Find(const DataType &aValue)
{
	int dataIndex = myData.Find(aValue);
	if(dataIndex < 0)
	{
		return false;
	}
	return true;
}
template <typename DataType>
void Stack<DataType>::DeleteAll()
{
	myData.RemoveAll();
	//myData.DeleteAll();
}
#endif