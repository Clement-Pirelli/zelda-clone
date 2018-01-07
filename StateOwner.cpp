#include "stdafx.h"
#include "StateOwner.h"
#include "StateManager.h"

StateOwner::StateOwner(StateManager& givenStateManager){
	myStateManager = &givenStateManager;
	myStateManager->addState("gameState", &myGameState);
	myStateManager->addState("gameOverState", &myGameOverState);
	myStateManager->setState("gameState");
}

StateOwner::~StateOwner(){
	myStateManager->removeState("gameState");
	myStateManager->removeState("gameOverState");
}