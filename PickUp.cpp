#include "stdafx.h"
#include "PickUp.h"
#include "RectangleCollider.h"
#include "RenderManager.h"
#include "LayerInfo.h"
#include "Service.h"
#include "EntityManager.h"
#include "RoomManager.h"

PickUp::PickUp(int givenX, int givenY){
	position.x = givenX;
	position.y = givenY;
	Service<EntityManager>::getService()->addEntity(this);
	myRenderManager = Service<RenderManager>::getService();
}

PickUp::~PickUp(){
	myRenderManager = nullptr;
	Service<EntityManager>::getService()->removeEntity(this);
}

void PickUp::onCollision(Entity* otherEntity){
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_PLAYER){
		pickedUp = true;
	}
}

Collider* PickUp::getCollider(){
	return myCollider;
}

SDL_Point PickUp::getPosition(){
	return position;
}

void PickUp::render(){
	myRenderManager->draw(getSprite(), position.x, position.y, LayerInfo::enemyLayer);
}

void PickUp::update(float givenDeltaTime){
	if (pickedUp == true || 
		Service<RoomManager>::getService()->getRoomChange() == true){
		delete this;
	}
}