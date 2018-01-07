#include "stdafx.h"
#include "GameOverState.h"
#include "GameState.h"
#include "InputManager.h"
#include "Service.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "RenderManager.h"

GameOverState::GameOverState(){
	myRenderManager = Service<RenderManager>::getService();
	myInputManager = Service<InputManager>::getService();
	gameOverSprite = Service<SpriteManager>::getService()->createSprite("../Assets/gameover.png", 0, 0, 161, 48);
}

GameOverState::~GameOverState(){
	Service<SpriteManager>::getService()->destroySprite(gameOverSprite);
	gameOverSprite = nullptr;
	myInputManager = nullptr;
	myRenderManager = nullptr;
}

void GameOverState::enter(){}

bool GameOverState::update(float deltaTime){
	myRenderManager->draw(gameOverSprite, GAME_OVER_SPRITE_POSITION.x, GAME_OVER_SPRITE_POSITION.y);
	if (myInputManager->isKeyReleased(SDL_SCANCODE_ESCAPE)){
		return false;
	} else {
		if (myInputManager->isKeyReleased(SDL_SCANCODE_RETURN)){
			Service<StateManager>::getService()->setState("gameState");
		}
	}
	return true;
}

void GameOverState::exit(){}

std::string GameOverState::getNextState(){
	return "";
}
