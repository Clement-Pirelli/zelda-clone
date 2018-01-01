#include "stdafx.h"
#include "BombEntity.h"
#include "RectangleCollider.h"
#include "RenderManager.h"
#include "LayerInfo.h"
#include "Service.h"
#include "SpriteManager.h"
#include "EntityManager.h"
#include "Sprite.h"

BombEntity::BombEntity(int givenX, int givenY){
	position.x = givenX;
	position.y = givenY;
	myRenderManager = Service <RenderManager> ::getService();
	mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/bomb.png", 0, 0, 16, 28);
	Service<EntityManager>::getService()->addEntity(this);
}

BombEntity::~BombEntity(){
	if (myCollider != nullptr) {
		delete myCollider;
		myCollider = nullptr;
	}
	Service<EntityManager>::getService()->removeEntity(this);
	mySprite = nullptr;
	myRenderManager = nullptr;

}

void BombEntity::update(float givenDeltaTime){
	timer += givenDeltaTime;
	if (exploded == true) {
		delete this;
	}
	if (timer >= deathTimer && exploded == false) {
		myCollider = new RectangleCollider(position.x - mySprite->getHeight(), position.y - mySprite->getHeight(), mySprite->getHeight() * 3, mySprite->getHeight() * 3);
		exploded = true;
	}
}

void BombEntity::render(){
	myRenderManager->draw(mySprite, position.x, position.y, LayerInfo::swordLayer);
	if (myCollider != nullptr) {
		myRenderManager->debugDrawRect(myCollider->getRectangle());
	}
}

Sprite* BombEntity::getSprite(){
	return mySprite;
}

Collider* BombEntity::getCollider(){
	return myCollider;
}

SDL_Point BombEntity::getPosition(){
	return position;
}

void BombEntity::onCollision(Entity* otherEntity){
}

ENTITYTYPE BombEntity::getType(){
	return ENTITYTYPE::ENTITY_BOMB;
}