#ifndef _STATE_STACK_HEADER_
#define _STATE_STACK_HEADER_

#include "GrowingArray.h"

class State;

class StateStack
{
public:
	StateStack(void);
	~StateStack(void);

	void Push(State* aState);
	void NakedPush(State* aState);
	void Pop();
	void Pop(int aNumberOfStatesToPush);

	int Count();

	void Update();

	void Render();
private:
	GrowingArray<State*> myStack;
};

#endif