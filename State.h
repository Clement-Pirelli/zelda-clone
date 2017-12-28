#pragma once
#include <string>

class State{
public:
	State(){};
	virtual ~State(){};
	virtual void enter() = 0;
	//when update returns false, StateManager knows it has to change the current state.
	virtual bool update(float deltaTime) = 0;
	virtual void exit() = 0;
	virtual std::string getNextState() = 0;
};