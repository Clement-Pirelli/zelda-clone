#include "stdafx.h"
#include "BOTTOMTEXT_State.h"
#include "BOTTOMTEXT_Entity.h"
#include "Service.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include <iostream>
//temp testing
#include "SpriteManager.h"
#include "Animation.h"
#include "Sprite.h"
#include "RenderManager.h"

//TODO : change this lmfao like what the fugg
std::string BOTTOMTEXT_State::nextState = "state 1";

//TODO : add the collision pairs we want for this state here
BOTTOMTEXT_State::BOTTOMTEXT_State(){
	CollisionManager::addCollisionPair(ENTITY_PLAYER, ENTITY_PLAYER);
	std::vector<Sprite*> tempSprites;
	//add more sprites to the tempSprites vector for all animations
	tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", 0, 0, 16, 16));
	tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", 1 * 16, 0, 16, 16));
	tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", 2 * 16, 0, 16, 16));
	tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", 3 * 16, 0, 16, 16));
	tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", 4 * 16, 0, 16, 16));
	myAnimation = new Animation(tempSprites);
	myEntityManager = new EntityManager();
	myPlayer = new BOTTOMTEXT_Entity(SDL_SCANCODE_A, SDL_SCANCODE_D, 100, 100);
	myEnemy = new BOTTOMTEXT_Entity(SDL_SCANCODE_J, SDL_SCANCODE_L, 300, 100);
	myEntityManager->addEntity(myPlayer);
	myEntityManager->addEntity(myEnemy);
	myInputManager = Service<InputManager>::getService();
}


BOTTOMTEXT_State::~BOTTOMTEXT_State(){
	delete myEntityManager;
	myEntityManager = nullptr;
	delete myPlayer;
	myPlayer = nullptr;
	delete myEnemy;
	myEnemy = nullptr;
}

//don't care about this
void BOTTOMTEXT_State::enter(){
	std::cout << "new state entered\n";
}

//don't care about this
bool BOTTOMTEXT_State::inputCheck()
{
	if (myInputManager->isKeyPressed(SDL_SCANCODE_W)) {
		(nextState == "state 2") ? (nextState = "state 1") : (nextState = "state 2");
		return false;
	}
	return true;
}

bool BOTTOMTEXT_State::update(float givenDeltaTime){

	myEntityManager->update(givenDeltaTime);
	myEntityManager->render();
	myAnimation->tick(givenDeltaTime);
	Service<RenderManager>().getService()->draw(myAnimation->getCurrentSprite(), 100, 100);
	checkCollision();
	return inputCheck();
}

//don't care about this
void BOTTOMTEXT_State::exit(){
	std::cout << "state exited\n";
}

//this is useful but I really ought to change where nextState is defined
std::string BOTTOMTEXT_State::getNextState(){
	return BOTTOMTEXT_State::nextState;
}

//this is useful
void BOTTOMTEXT_State::checkCollision(){
	std::vector<Entity*> entities = myEntityManager->getAllEntities();
	for (unsigned int i = 0; i < entities.size(); i++) {
		for (unsigned int j = 0; j < entities.size(); j++) {
			if (j == i) {
				continue;
			}
			if (CollisionManager::checkIfColliding(entities[i], entities[j])) {
				entities[i]->onCollision(entities[j]);
				entities[j]->onCollision(entities[i]);
			}
		}
	}
}
