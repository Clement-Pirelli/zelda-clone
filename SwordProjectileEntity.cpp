#include "stdafx.h"
#include "SwordProjectileEntity.h"
#include "RectangleCollider.h"
#include "Sprite.h"
#include "Service.h"
#include "SpriteManager.h"
#include "RenderManager.h"
#include "FirstSwordEntity.h"
#include "RoomManager.h"
#include "Room.h"
#include "EntityManager.h"
#include "LayerInfo.h"

SwordProjectileEntity::SwordProjectileEntity(FirstSwordEntity* givenSword){
	position.x = givenSword->getPosition().x;
	position.y = givenSword->getPosition().y;
	switch (givenSword->getDirection()) {
		//add origin and velocity changes
	case SWORDDIRECTION::S_DOWN:
		mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/sword_vertical.png", 0, 0, 16, 32);
		mySprite->setFlip(SDL_FLIP_VERTICAL);
		velocity.y = speed;
		break;
	case SWORDDIRECTION::S_UP:
		mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/sword_vertical.png", 0, 0, 16, 32);
		velocity.y = -speed;
		break;
	case SWORDDIRECTION::S_RIGHT:
		mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/sword.png", 0, 0, 32, 16);
		velocity.x = speed;
		break;
	case SWORDDIRECTION::S_LEFT:
		mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/sword.png", 0, 0, 32, 16);
		mySprite->setFlip(SDL_FLIP_HORIZONTAL);
		velocity.x = -speed;
		break;
	}
	myCollider = new RectangleCollider(position.x, position.y, mySprite->getWidth(), mySprite->getHeight());
	myRenderManager = Service<RenderManager>::getService();
}

SwordProjectileEntity::~SwordProjectileEntity(){
	mySprite = nullptr;
	delete myCollider;
	myCollider = nullptr;
	myRenderManager = nullptr;
	Service<EntityManager>::getService()->removeEntity(this);
}

void SwordProjectileEntity::update(float givenDeltaTime){
	position.x += velocity.x;
	position.y += velocity.y;
	myCollider->setPosition(position.x, position.y);
	if	(position.x < 0
		|| position.x + mySprite->getWidth() > Service<RoomManager>::getService()->getCurrentRoom()->getWidthInPixels()
		|| position.y < 0
		|| position.y + mySprite->getHeight() >Service<RoomManager>::getService()->getCurrentRoom()->getHeightInPixels()
		) {
		delete this;
	}
	if (Service<RoomManager>::getService()->getRoomChange() == true) {
		delete this;
	}
}

void SwordProjectileEntity::render(){
	myRenderManager->draw(mySprite, position.x, position.y, LayerInfo::swordLayer);
	myRenderManager->debugDrawRect(myCollider->getRectangle());
}

Sprite* SwordProjectileEntity::getSprite(){
	return mySprite;
}

Collider* SwordProjectileEntity::getCollider(){
	return myCollider;
}

void SwordProjectileEntity::onCollision(Entity* otherEntity){
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_ENEMY) {
		delete this;
	}
}

ENTITYTYPE SwordProjectileEntity::getType(){
	return ENTITYTYPE::ENTITY_SWORD;
}