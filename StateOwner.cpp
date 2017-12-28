#include "stdafx.h"
#include "StateOwner.h"
#include "StateManager.h"

StateOwner::StateOwner(){}


StateOwner::StateOwner(StateManager& givenStateManager){
	myStateManager = &givenStateManager;
	myStateManager->addState("gameState", &myState);
	myStateManager->setState("gameState");
}

StateOwner::~StateOwner(){
	myStateManager->removeState("gameState");
}
