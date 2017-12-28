#include "stdafx.h"
#include "StateManager.h"
#include "State.h"

StateManager::StateManager(){
}


StateManager::~StateManager(){
}

void StateManager::addState(std::string givenIdentifier, State * givenState){
	auto iterator = states.find(givenIdentifier);
	if(iterator == states.end()){
		states.insert(std::pair<std::string, State*>(givenIdentifier, givenState));
	}
}

void StateManager::removeState(std::string givenIdentifier){
	states.erase(givenIdentifier);
}

void StateManager::setState(std::string givenIdentifier){
	auto iterator = states.find(givenIdentifier);
	if (iterator == states.end()) {
		return;
	}
	if (currentState != nullptr) {
		currentState->exit();
	}
	currentState = iterator->second;
}

bool StateManager::update(float givenDeltaTime){
	if (currentState == nullptr) {
		return false;
	}
	if (currentState->update(givenDeltaTime) == false) {
		changeState();
	}
	return true;
}

void StateManager::changeState(){
	std::string nextState = currentState->getNextState();
	auto iterator = states.find(nextState);
	if (iterator == states.end()) {
		return;
	}
	currentState->exit();
	currentState = iterator->second;
	currentState->enter();
}
