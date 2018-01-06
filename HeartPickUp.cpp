#include "stdafx.h"
#include "HeartPickUp.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "RectangleCollider.h"

HeartPickUp::HeartPickUp(int givenX, int givenY) : PickUp(givenX, givenY){
	mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/heart_pickup.png", 0, 0, 26, 28);
	myCollider = new RectangleCollider(position.x, position.y, mySprite->getWidth(), mySprite->getHeight());
}

HeartPickUp::~HeartPickUp(){
	delete myCollider;
	myCollider = nullptr;
	mySprite = nullptr;
}

Sprite* HeartPickUp::getSprite(){
	return mySprite;
}

ENTITYTYPE HeartPickUp::getType(){
	return ENTITYTYPE::ENTITY_HEART_PICKUP;
}