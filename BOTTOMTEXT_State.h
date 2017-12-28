#pragma once
#include "State.h"

class BOTTOMTEXT_Entity;
class EntityManager;
class InputManager;
class Animation;

class BOTTOMTEXT_State : public State{
public:
	BOTTOMTEXT_State();
	~BOTTOMTEXT_State();
	void enter();
	bool inputCheck();
	//when update returns false, StateManager knows it has to change the current state.
	bool update(float givenDeltaTime);
	void exit();
	std::string getNextState() override;
private:
	//temp for testing
	Animation* myAnimation = nullptr;
	void checkCollision();
	BOTTOMTEXT_Entity* myPlayer;
	BOTTOMTEXT_Entity* myEnemy;
	InputManager* myInputManager;
	EntityManager* myEntityManager;
	static std::string nextState;
};