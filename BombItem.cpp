#include "stdafx.h"
#include "BombItem.h"
#include "BombEntity.h"
#include "PlayerAvatar.h"

BombItem::BombItem(){
}


BombItem::~BombItem(){
}

void BombItem::use(PlayerAvatar* givenPlayer){
	new BombEntity(givenPlayer->getPosition().x, givenPlayer->getPosition().y);
}