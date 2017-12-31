#include "stdafx.h"
#include "Enemy.h"
#include "RenderManager.h"
#include "Service.h"
#include "RectangleCollider.h"

Enemy::Enemy(){
	myRenderManager = Service<RenderManager>::getService();
}

Enemy::~Enemy(){
	myRenderManager = nullptr;
}

int Enemy::getDamage(){
	return damage;
}

Collider* Enemy::getCollider() {
	return myCollider;
}

ENTITYTYPE Enemy::getType(){
	return ENTITYTYPE::ENTITY_ENEMY;
}

SDL_Point Enemy::getPosition(){
	return position;
}
