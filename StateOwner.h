#pragma once
#include "GameState.h"
#include "GameOverState.h"

class StateManager;

class StateOwner{
public:
	StateOwner(StateManager& givenStateManager);
	~StateOwner();
private:
	StateManager* myStateManager = nullptr;
	GameState myGameState;
	GameOverState myGameOverState;
};

