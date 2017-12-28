#pragma once
#include "State.h"
#include <string>

class EntityManager;
class RoomManager;

class GameState : public State{
public:
	GameState();
	~GameState();
	//TODO : Check the newest Tiberius file : I think we do nothing in the enter and exit functions but could be wrong
	void enter() override {};
	bool update(float deltaTime) override;
	void exit() override {};
	std::string getNextState() override;
private:
	void checkCollision();
	bool paused = false;
	EntityManager* myEntityManager = nullptr;
	RoomManager* myRoomManager = nullptr;
};

