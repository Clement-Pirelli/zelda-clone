#include "stdafx.h"
#include "FirstSwordItem.h"
#include "FirstSwordEntity.h"
#include "SwordProjectileEntity.h"
#include "PlayerAvatar.h"
#include "Service.h"
#include "EntityManager.h"

FirstSwordItem::FirstSwordItem(){
}

FirstSwordItem::~FirstSwordItem(){
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