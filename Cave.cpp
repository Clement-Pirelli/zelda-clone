#include "stdafx.h"
#include "Cave.h"
#include "Sprite.h"
#include "Service.h"
#include "SpriteManager.h"
#include "RoomManager.h"
#include "Room.h"
#include "RectangleCollider.h"
#include "LayerInfo.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "PlayerAvatar.h"


Cave::Cave(std::string givenFilePath, int givenX, int givenY, ROOMTILETYPE givenTileType, bool isOpened) : Obstacle(givenFilePath, givenX, givenY, givenTileType){
	opened = isOpened;
}

Cave::~Cave(){
}

void Cave::setOpened(){
	opened = true;
}

Collider* Cave::getCollider(){
	return myCollider;
}

void Cave::render(){
	if (opened == false){
		myRenderManager->draw(mySprite, position.x, position.y, LayerInfo::tileLayer);
	}
}

void Cave::onCollision(Entity* otherEntity){
	if (opened == true) {
		if (otherEntity->getType() == ENTITYTYPE::ENTITY_PLAYER) {
			//sets the room as the one to the right of the current room. This means that the "cave" room must be on the right of the current room, but be inaccessible through any other means
			//since the room is changed during the onCollision function, the player's onCollision is not called since the entity it is colliding with is no longer accessible. We must therefore set the player's position here
			Service<RoomManager>::getService()->changeRoom(Service<RoomManager>::getService()->getCurrentRow(), Service<RoomManager>::getService()->getCurrentColumn() + 1);
		}
	}
	else {
		if (otherEntity->getType() == ENTITYTYPE::ENTITY_BOMB) {
			opened = true;
		}
	}
}

ENTITYTYPE Cave::getType(){
	if (opened == false) {
		return ENTITYTYPE::ENTITY_OBSTACLE;
	}
	else {
		return ENTITYTYPE::ENTITY_CAVE;
	}
}
