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
	Service<EntityManager>::getService()->addEntity(this);
	myRenderManager = Service<RenderManager>::getService();
	
	switch (givenDirection) {
	case ENEMYDIRECTION::E_DOWN:
		velocityY += speed;
		mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/bullet.png", 0, 0, 16, 20);
		mySprite->setFlip(SDL_FLIP_VERTICAL);
		break;
	case ENEMYDIRECTION::E_UP:
		velocityY -= speed;
		mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/bullet.png", 0, 0, 16, 20);
		break;
	case ENEMYDIRECTION::E_LEFT:
		velocityX -= speed;
		mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/bullet_horizontal.png", 0, 0, 20, 16);
		break;
	case ENEMYDIRECTION::E_RIGHT:
		velocityX += speed;
		mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/bullet_horizontal.png", 0, 0, 20, 16);
		mySprite->setFlip(SDL_FLIP_HORIZONTAL);
		break;
	}
	myCollider = new RectangleCollider(position.x, position.y, getSprite()->getWidth(), getSprite()->getHeight());
}

EnemyBulletEntity::~EnemyBulletEntity(){
	delete myCollider;
	myCollider = nullptr;
	mySprite = nullptr;
	myRenderManager = nullptr;
	Service<EntityManager>::getService()->removeEntity(this);
}

void EnemyBulletEntity::update(float givenDeltaTime){
	position.x += velocityX;
	position.y += velocityY;
	if (position.x < 0
		|| position.x + mySprite->getWidth() > Service<RoomManager>::getService()->getCurrentRoom()->getWidthInPixels()
		|| position.y < 0
		|| position.y + mySprite->getHeight() >Service<RoomManager>::getService()->getCurrentRoom()->getHeightInPixels()
		) {
		delete this;
	}
}

void EnemyBulletEntity::render(){
	myRenderManager->draw(mySprite, position.x, position.y, LayerInfo::bulletLayer);
}

Sprite* EnemyBulletEntity::getSprite(){
	return mySprite;
}

Collider* EnemyBulletEntity::getCollider(){
	return myCollider;
}

void EnemyBulletEntity::onCollision(Entity* otherEntity){
}

ENTITYTYPE EnemyBulletEntity::getType(){
	return ENTITYTYPE::ENTITY_BULLET;
}
