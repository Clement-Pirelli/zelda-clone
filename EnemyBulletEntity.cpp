#include "stdafx.h"
#include "EnemyBulletEntity.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "RectangleCollider.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "RoomManager.h"
#include "Room.h"
#include "Enemy.h"
#include "LayerInfo.h"

EnemyBulletEntity::EnemyBulletEntity(int givenX, int givenY, ENEMYDIRECTION givenDirection){
	position.x = givenX;
	position.y = givenY;
	Service<EntityManager>::getService()->addEntity(this);
	myRenderManager = Service<RenderManager>::getService();
	switch (givenDirection) {
	case ENEMYDIRECTION::E_DOWN:
		velocity.y += speed;
		mySprite = Service<SpriteManager>::getService()->createSprite(verticalSpriteFilePath, 0, 0, 16, 20);
		mySprite->setFlip(SDL_FLIP_VERTICAL);
		break;
	case ENEMYDIRECTION::E_UP:
		velocity.y -= speed;
		mySprite = Service<SpriteManager>::getService()->createSprite(verticalSpriteFilePath, 0, 0, 16, 20);
		break;
	case ENEMYDIRECTION::E_LEFT:
		velocity.x -= speed;
		mySprite = Service<SpriteManager>::getService()->createSprite(horizontalSpriteFilePath, 0, 0, 20, 16);
		break;
	case ENEMYDIRECTION::E_RIGHT:
		velocity.x += speed;
		mySprite = Service<SpriteManager>::getService()->createSprite(horizontalSpriteFilePath, 0, 0, 20, 16);
		mySprite->setFlip(SDL_FLIP_HORIZONTAL);
		break;
	}
	myCollider = new RectangleCollider(position.x, position.y, mySprite->getWidth(), mySprite->getHeight());
}

EnemyBulletEntity::~EnemyBulletEntity(){
	delete myCollider;
	myCollider = nullptr;
	Service<SpriteManager>::getService()->destroySprite(mySprite);
	mySprite = nullptr;
	myRenderManager = nullptr;
	Service<EntityManager>::getService()->removeEntity(this);
}

void EnemyBulletEntity::update(float givenDeltaTime){
	position.x += velocity.x;
	position.y += velocity.y;
	myCollider->setPosition(position.x, position.y);
	if (position.x < 0
		|| position.x + mySprite->getWidth() > Service<RoomManager>::getService()->getCurrentRoom()->getWidthInPixels()
		|| position.y < 0
		|| position.y + mySprite->getHeight() >Service<RoomManager>::getService()->getCurrentRoom()->getHeightInPixels()
		|| collidedWithPlayer == true) {
		delete this;
	}
}

void EnemyBulletEntity::render(){
	myRenderManager->draw(mySprite, position.x, position.y, LayerInfo::bulletLayer);
	myRenderManager->debugDrawRect(myCollider->getRectangle());
}

Sprite* EnemyBulletEntity::getSprite(){
	return mySprite;
}

Collider* EnemyBulletEntity::getCollider(){
	return myCollider;
}

void EnemyBulletEntity::onCollision(Entity* otherEntity){
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_PLAYER) {
		collidedWithPlayer = true;
	}
}

ENTITYTYPE EnemyBulletEntity::getType(){
	return ENTITYTYPE::ENTITY_BULLET;
}

SDL_Point EnemyBulletEntity::getPosition(){
	return position;
}

SDL_Point EnemyBulletEntity::getVelocity(){
	return velocity;
}

int EnemyBulletEntity::getDamage(){
	return damage;
}
