#include "stdafx.h"
#include "FairyPickUp.h"
#include "Animation.h"
#include "Sprite.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Utilities.h"
#include "RoomManager.h"
#include "RectangleCollider.h"

FairyPickUp::FairyPickUp(int givenX, int givenY) : PickUp(givenX, givenY){
	std::vector<Sprite*> tempSprites;
	tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/fairy.png", 0, 0, 16, 32));
	tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/fairy.png", 16, 0, 16, 32));
	myAnimation = new Animation(tempSprites, 1.0f);
	velocity.x = Utilities::random(1, 2);
	velocity.y = Utilities::random(1, 2);
	myCollider = new RectangleCollider(position.x, position.y, myAnimation->getCurrentSprite()->getWidth(), myAnimation->getCurrentSprite()->getHeight());
}


FairyPickUp::~FairyPickUp(){
	delete myCollider;
	myCollider = nullptr;
	delete myAnimation;
	myAnimation = nullptr;
}

void FairyPickUp::update(float givenDeltaTime){
	
	position.x += velocity.x;
	position.y += velocity.y;
	myAnimation->tick(givenDeltaTime);
	myCollider->setPosition(position.x, position.y);
	timer += givenDeltaTime;
	if(timer >= deathTimer ||
		pickedUp == true ||
		Service<RoomManager>::getService()->getRoomChange() == true){
		delete this;
	}
}

Sprite* FairyPickUp::getSprite(){
	return myAnimation->getCurrentSprite();
}

ENTITYTYPE FairyPickUp::getType(){
	return ENTITYTYPE::ENTITY_FAIRY_PICKUP;
}
