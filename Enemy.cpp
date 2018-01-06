#include "stdafx.h"
#include "Enemy.h"
#include "RenderManager.h"
#include "Service.h"
#include "RectangleCollider.h"
#include "BombPickUp.h"
#include "HeartPickUp.h"
#include "FairyPickUp.h"
#include "KeyPickUp.h"
#include "RupeePickUp.h"
#include "Utilities.h"

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

SDL_Point Enemy::getVelocity(){
	return velocity;
}

void Enemy::spawnPickUp(){
	PickUp* p = nullptr;
	int r = Utilities::random(1, 10);
	if (r == 4){
		p = new KeyPickUp(position.x, position.y);
	}
	if (r == 5){
		p = new HeartPickUp(position.x, position.y);
	}
	if (r == 6){
		p = new FairyPickUp(position.x, position.y);
	}
	if (r == 7){
		p = new RupeePickUp(position.x, position.y);
	}
	if (r >= 8){
		p = new BombPickUp(position.x, position.y);
	}
}
