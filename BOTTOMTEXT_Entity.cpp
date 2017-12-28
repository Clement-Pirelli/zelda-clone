#include "stdafx.h"
#include "BOTTOMTEXT_Entity.h"
#include "Service.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"
#include "Sprite.h"
#include <iostream>


BOTTOMTEXT_Entity::BOTTOMTEXT_Entity(SDL_Scancode givenLeftKey, SDL_Scancode givenRightKey, int givenX, int givenY){
	myInputManager = Service<InputManager>::getService();
	myRenderManager = Service<RenderManager>::getService();
	mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/xd.png", 0, 0, 70, 100);
	myCollider = new RectangleCollider(givenX, givenY, mySprite->getWidth(), mySprite->getHeight());
	position.x = givenX;
	position.y = givenY;
	rightKey = givenRightKey;
	leftKey = givenLeftKey;
	mySprite->setOrigin(Sprite::ORIGIN::CENTER);
}

BOTTOMTEXT_Entity::~BOTTOMTEXT_Entity(){
	Service<SpriteManager>::getService()->destroySprite(mySprite);
	delete myCollider;
	myCollider = nullptr;
}

void BOTTOMTEXT_Entity::update(float givenDeltaTime){
	//change this stuff to instead of changing the position directly, changing the velocity of the player, which then changes the position in the update
	//that way we can set the direction of the sprite and its animation in a proper fashion
	if (myInputManager->isKeyDown(leftKey)) {
		mySprite->setFlip(SDL_FLIP_HORIZONTAL);
		position.x -= speed;
	}
	if (myInputManager->isKeyDown(rightKey)) {
		mySprite->setFlip(SDL_FLIP_NONE);
		position.x += speed;
	}
	myCollider->setPosition(position.x, position.y);
}

void BOTTOMTEXT_Entity::render(){
	myRenderManager->draw(mySprite, position.x, position.y);
	myRenderManager->debugDrawRect(myCollider->getRectangle());
}

Sprite * BOTTOMTEXT_Entity::getSprite(){
	return mySprite;
}

Collider* BOTTOMTEXT_Entity::getCollider(){
	return myCollider;
}

void BOTTOMTEXT_Entity::onCollision(Entity* otherEntity){
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_PLAYER) {
		std::cout << "COLLISIOON AAAAAAAAAAAAAAAAA\n";
	}
}

ENTITYTYPE BOTTOMTEXT_Entity::getType(){
	return ENTITYTYPE::ENTITY_PLAYER;
}
