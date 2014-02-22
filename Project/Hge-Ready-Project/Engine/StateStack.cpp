#include "StateStack.h"
#include "State.h"

StateStack::StateStack(void)
:	myStack(4)
{
}

StateStack::~StateStack(void)
{
}

void StateStack::Push(State* aState)
{
	aState->Init();
	myStack.Add(aState);
}

void StateStack::NakedPush(State* aState)
{
	myStack.Add(aState);
}

void StateStack::Pop()
{
	myStack.DeleteLast();
}

void StateStack::Pop(int aNumberOfStatesToPush)
{
	for(int i=0;i<aNumberOfStatesToPush;i++)
	{
		myStack.DeleteLast();
	}
}

int StateStack::Count()
{
	return myStack.Count();
}

void StateStack::Update()
{
	if(myStack.GetLast()->Update() != STATE_OK)
	{
		Pop();
	}
}

void StateStack::Render()
{
	if(myStack.Count() > 0)
	{
		myStack.GetLast()->Render();
	}
}