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

Cave::Cave(std::string givenFilePath, int givenX, int givenY, ROOMTILETYPE givenTileType) : Obstacle(givenFilePath, givenX, givenY, givenTileType){
}

Cave::~Cave(){
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
		return ENTITYTYPE::ENTITY_CAVE;
	}
	else {
		return ENTITYTYPE::ENTITY_TILE;
	}
}
