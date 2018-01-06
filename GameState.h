#pragma once
#include "State.h"
#include <string>

class EntityManager;
class RoomManager;
class InputManager;
class PlayerAvatar;
class UI;
class NumberFont;

class GameState : public State{
public:
	GameState();
	~GameState();
	void enter() override;
	bool update(float deltaTime) override;
	void exit() override;
	std::string getNextState() override;
private:
	void checkCollision();
	void checkInput();
	void createRooms();
	bool paused = false;
	PlayerAvatar* myPlayer = nullptr;
	InputManager* myInputManager = nullptr;
	EntityManager* myEntityManager = nullptr;
	RoomManager* myRoomManager = nullptr;
	UI* myUI = nullptr;
	NumberFont* myFont = nullptr;
	const SDL_Scancode inventoryKey = SDL_SCANCODE_ESCAPE;
};

