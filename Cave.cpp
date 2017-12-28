#include "stdafx.h"
#include "Cave.h"
#include "Sprite.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Room.h"
#include "RectangleCollider.h"

Cave::Cave(std::string givenFilePath, int givenX, int givenY, ROOMTILETYPE givenTileType) : Obstacle(givenFilePath, givenX, givenY, givenTileType){
	openedSprite = Service<SpriteManager>::getService()->createSprite(givenFilePath, ROOMTILETYPE::CAVE * Room::tileWidth, 0, Room::tileWidth, Room::tileHeight);
}

Cave::~Cave(){
}

Collider* Cave::getCollider(){
	return myCollider;
}

void Cave::onCollision(Entity* otherEntity){
}

ENTITYTYPE Cave::getType(){
	if (opened == false) {
		return ENTITYTYPE::ENTITY_HIDDEN_CAVE;
	}
	else {
		return ENTITYTYPE::ENTITY_TILE;
	}
}
