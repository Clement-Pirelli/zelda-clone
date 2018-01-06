#include "stdafx.h"
#include "RupeePickUp.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Service.h"
#include "Animation.h"
#include "RoomManager.h"
#include "RectangleCollider.h"

RupeePickUp::RupeePickUp(int givenX, int givenY) : PickUp(givenX, givenY){
	std::vector<Sprite*> tempSprites;
	tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/rupees.png", 0, 0, 16, 32));
	tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/rupees.png", 16, 0, 16, 32));
	myAnimation = new Animation(tempSprites, 0.4f);
	myCollider = new RectangleCollider(position.x, position.y, myAnimation->getCurrentSprite()->getWidth(), myAnimation->getCurrentSprite()->getHeight());
}

RupeePickUp::~RupeePickUp(){
	delete myCollider;
	myCollider = nullptr;
	delete myAnimation;
	myAnimation = nullptr;
}

void RupeePickUp::update(float givenDeltaTime){
	myAnimation->tick(givenDeltaTime);
	if (pickedUp == true ||
		Service<RoomManager>::getService()->getRoomChange() == true){
		delete this;
	}
}

Sprite* RupeePickUp::getSprite(){
	return myAnimation->getCurrentSprite();
}

ENTITYTYPE RupeePickUp::getType(){
	return ENTITYTYPE::ENTITY_RUPEE_PICKUP;
}
