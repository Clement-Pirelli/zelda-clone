#pragma once
#include "State.h"

class InputManager;
class Sprite;

class GameOverState : public State {
public:
	GameOverState();
	~GameOverState();
	void enter();
	//when update returns false, StateManager knows it has to change the current state.
	bool update(float deltaTime);
	void exit();
	std::string getNextState();
private:
	InputManager* myInputManager = nullptr;
	Sprite* gameOverSprite = nullptr;
	const SDL_Point GAME_OVER_SPRITE_POSITION{ 100, 100 };
};

