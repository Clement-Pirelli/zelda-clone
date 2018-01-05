#include "stdafx.h"
#include "FirstSwordItem.h"
#include "FirstSwordEntity.h"
#include "SwordProjectileEntity.h"
#include "PlayerAvatar.h"
#include "Service.h"
#include "EntityManager.h"
#include "SpriteManager.h"

FirstSwordItem::FirstSwordItem(){
	displaySprite = Service<SpriteManager>::getService()->createSprite("../Assets/firstsword_UI.png", 0, 0, displaySpriteDimension, displaySpriteDimension);
}

FirstSwordItem::~FirstSwordItem(){
	displaySprite = nullptr;
}

void FirstSwordItem::use(PlayerAvatar* givenPlayer){
	if (active == false) {
		if (mySwordEntity == nullptr) {
			mySwordEntity = new FirstSwordEntity(givenPlayer);
		}
		else {
			mySwordEntity->reposition(givenPlayer);
		}
		Service<EntityManager>::getService()->addEntity(mySwordEntity);
		active = true;
	}
	mySwordEntity->setCollisionActive(true);
}

void FirstSwordItem::stopUse(){
	Service<EntityManager>::getService()->removeEntity(mySwordEntity);
	active = false;
	mySwordEntity->setCollisionActive(false);
}

void FirstSwordItem::useFullHealth(){
	Service<EntityManager>::getService()->addEntity(new SwordProjectileEntity(mySwordEntity));
}