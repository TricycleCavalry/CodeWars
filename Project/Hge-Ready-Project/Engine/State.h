#ifndef _STATE_HEADER_
#define _STATE_HEADER_

class StateStack;
class Engine;

enum StateReturnIndexes
{
	STATE_OK,
};

class State
{
public:
	State(StateStack& aStateStack, Engine* anEngine)
	:	myStateStack(aStateStack)
	,	myEngine(anEngine){}

	virtual ~State(){}

	virtual void Init()=0;

	virtual int Update()=0;
	virtual void Render()=0;
protected:
	StateStack& myStateStack;
	Engine* myEngine;
};

#endif