#include "stdafx.h"
#include "BombPickUp.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Service.h"
#include "RectangleCollider.h"

BombPickUp::BombPickUp(int givenX, int givenY) : PickUp(givenX, givenY){
	mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/bomb.png", 0, 0, 16, 28);
	myCollider = new RectangleCollider(position.x, position.y, mySprite->getWidth(), mySprite->getHeight());
}

BombPickUp::~BombPickUp(){
	delete myCollider;
	myCollider = nullptr;
	mySprite = nullptr;
}

Sprite* BombPickUp::getSprite(){
	return mySprite;
}

ENTITYTYPE BombPickUp::getType(){
	return ENTITYTYPE::ENTITY_BOMB_PICKUP;
}
