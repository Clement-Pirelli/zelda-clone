#pragma once
#include "GameState.h"
class StateManager;

class StateOwner{
public:
	StateOwner(StateManager& givenStateManager);
	~StateOwner();
private:
	StateOwner();
	StateManager* myStateManager = nullptr;
	GameState myState;
};

