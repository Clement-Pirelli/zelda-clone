#include "stdafx.h"
#include "KeyPickUp.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Service.h"
#include "RectangleCollider.h"

KeyPickUp::KeyPickUp(int givenX, int givenY) : PickUp(givenX, givenY){
	mySprite = Service<SpriteManager>::getService()->createSprite("../Assets/key.png", 0, 0, 16, 32);
	myCollider = new RectangleCollider(position.x, position.y, mySprite->getWidth(), mySprite->getHeight());
}


KeyPickUp::~KeyPickUp(){
	delete myCollider;
	myCollider = nullptr;
	mySprite = nullptr;
}

Sprite* KeyPickUp::getSprite(){
	return mySprite;
}

ENTITYTYPE KeyPickUp::getType(){
	return ENTITYTYPE::ENTITY_KEY_PICKUP;
}
