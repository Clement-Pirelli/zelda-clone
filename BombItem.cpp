#include "stdafx.h"
#include "BombItem.h"
#include "BombEntity.h"
#include "PlayerAvatar.h"
#include "Service.h"
#include "Sprite.h"
#include "SpriteManager.h"

BombItem::BombItem(){
	displaySprite = Service<SpriteManager>::getService()->createSprite("../Assets/bomb_UI.png", 0, 0, displaySpriteDimension, displaySpriteDimension);
}


BombItem::~BombItem(){
	Service<SpriteManager>::getService()->destroySprite(displaySprite);
	displaySprite = nullptr;
}

void BombItem::use(PlayerAvatar* givenPlayer){
	if (bombCount > 0){
		bombCount--;
		new BombEntity(givenPlayer->getPosition().x, givenPlayer->getPosition().y);
	}
}

int BombItem::getBombCount(){
	return bombCount;
}

void BombItem::addBomb(){
	bombCount++;
}