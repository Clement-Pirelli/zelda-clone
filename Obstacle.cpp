#include "stdafx.h"
#include "Obstacle.h"
#include "RectangleCollider.h"
#include "Sprite.h"

Obstacle::Obstacle(std::string givenFilePath, int givenX, int givenY, ROOMTILETYPE givenTileType) : Tile(givenFilePath, givenX, givenY, givenTileType){
	myCollider = new RectangleCollider(position.x, position.y, mySprite->getWidth(), mySprite->getHeight());
}

Obstacle::~Obstacle(){
	delete myCollider;
	myCollider = nullptr;
}

Collider* Obstacle::getCollider(){
	return myCollider;
}

void Obstacle::onCollision(Entity * otherEntity){
}

ENTITYTYPE Obstacle::getType(){
	return ENTITYTYPE::ENTITY_OBSTACLE;
}
