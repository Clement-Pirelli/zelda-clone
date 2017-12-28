#pragma once
#include <map>
#include <string>

class State;

class StateManager{
public:
	StateManager();
	~StateManager();
	void addState(std::string givenIdentifier, State* givenState);
	void removeState(std::string givenIdentifier);
	void setState(std::string givenIdentifier);
	bool update(float givenDeltaTime);
private:
	State* currentState = nullptr;
	std::map<std::string, State*> states;
	void changeState(); //changes the current state to what the current state tells us to change it to
};

