#include "stdafx.h"
#include "SwordEntity.h"
#include "PlayerAvatar.h"
#include "Sprite.h"
#include "Service.h"
#include "SpriteManager.h"
#include "RectangleCollider.h"



SwordEntity::SwordEntity(){
}


SwordEntity::~SwordEntity(){
}

void SwordEntity::reposition(PlayerAvatar* givenPlayer){
	//we assume that every sword sprite is the same width and height
	int playerWidth = givenPlayer->getSprite()->getWidth();
	int playerHeight = givenPlayer->getSprite()->getHeight();
	switch (givenPlayer->getDirection()) {
		//add origin and velocity changes
	case PLAYERDIRECTION::DOWN:
		direction = SWORDDIRECTION::S_DOWN;
		mySprite = Service<SpriteManager>::getService()->createSprite(verticalSpriteFilePath, 0, 0, 16, 32);
		mySprite->setFlip(SDL_FLIP_VERTICAL);
		position.x = givenPlayer->getPosition().x + playerWidth / 2 - mySprite->getWidth() / 2;
		position.y = givenPlayer->getPosition().y + playerHeight - mySprite->getHeight() / 4;
		break;
	case PLAYERDIRECTION::UP:
		direction = SWORDDIRECTION::S_UP;
		mySprite = Service<SpriteManager>::getService()->createSprite(verticalSpriteFilePath, 0, 0, 16, 32);
		position.x = givenPlayer->getPosition().x + playerWidth / 2 - mySprite->getWidth() / 2;
		position.y = givenPlayer->getPosition().y - playerHeight + mySprite->getHeight() / 3;
		break;
	case PLAYERDIRECTION::RIGHT:
		direction = SWORDDIRECTION::S_RIGHT;
		mySprite = Service<SpriteManager>::getService()->createSprite(horizontalSpriteFilePath, 0, 0, 32, 16);
		position.x = givenPlayer->getPosition().x + playerWidth - mySprite->getWidth() / 3 - 1;
		position.y = givenPlayer->getPosition().y + playerHeight / 3 + 1;
		break;
	case PLAYERDIRECTION::LEFT:
		direction = SWORDDIRECTION::S_LEFT;
		mySprite = Service<SpriteManager>::getService()->createSprite(horizontalSpriteFilePath, 0, 0, 32, 16);
		mySprite->setFlip(SDL_FLIP_HORIZONTAL);
		position.x = givenPlayer->getPosition().x - playerWidth + mySprite->getWidth() / 3 + 1;
		position.y = givenPlayer->getPosition().y + playerHeight / 3 + 1;
		break;
	}
}

void SwordEntity::setCollisionActive(bool givenActive){
	collisionActive = givenActive;
}

SWORDDIRECTION SwordEntity::getDirection(){
	return direction;
}

SDL_Point SwordEntity::getPosition(){
	return position;
}

Collider* SwordEntity::getCollider(){
	if (collisionActive == true) {
		return myCollider;
	}
	return nullptr;
}

ENTITYTYPE SwordEntity::getType(){
	return ENTITYTYPE::ENTITY_SWORD;
}

Sprite* SwordEntity::getSprite(){
	return mySprite;
}
