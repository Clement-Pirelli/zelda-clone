#include "stdafx.h"
#include "GameOverState.h"
#include "GameState.h"
#include "InputManager.h"
#include "Service.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "StateManager.h"

GameOverState::GameOverState(){
	myInputManager = Service<InputManager>::getService();
	gameOverSprite = Service<SpriteManager>::getService()->createSprite("../Assets/gameover.png", GAME_OVER_SPRITE_POSITION.x, GAME_OVER_SPRITE_POSITION.y, 161, 48);
}


GameOverState::~GameOverState(){
	gameOverSprite = nullptr;
	myInputManager = nullptr;
}

void GameOverState::enter(){}

bool GameOverState::update(float deltaTime){
	if (myInputManager->isKeyReleased(SDL_SCANCODE_RETURN)){
		return false;
	} else {
		if (myInputManager->isKeyReleased(SDL_SCANCODE_ESCAPE)){
			Service<StateManager>::getService()->removeState("gameState");
			Service<StateManager>::getService()->addState("gameState", new GameState());
			Service<StateManager>::getService()->setState("gameState");
		}
	}
	return true;
}

void GameOverState::exit(){}

std::string GameOverState::getNextState(){
	return "";
}
