#include "stdafx.h"
#include "FirstSwordEntity.h"
#include "Service.h"
#include "RectangleCollider.h"
#include "RenderManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Service.h"
#include "EntityManager.h"
#include "SwordProjectileEntity.h"
#include "PlayerAvatar.h"
#include "LayerInfo.h"

FirstSwordEntity::FirstSwordEntity(PlayerAvatar* givenPlayer){
	verticalSpriteFilePath = "../Assets/sword_vertical.png";
	horizontalSpriteFilePath = "../Assets/sword.png";
	reposition(givenPlayer);
	myCollider = new RectangleCollider(position.x, position.y, mySprite->getWidth(), mySprite->getHeight());
	myRenderManager = Service<RenderManager>::getService();
}

FirstSwordEntity::~FirstSwordEntity(){
	myRenderManager = nullptr;
	Service<SpriteManager>::getService()->destroySprite(mySprite);
	mySprite = nullptr;
	delete myCollider;
	myCollider = nullptr;
}

void FirstSwordEntity::update(float givenDeltaTime){
	myCollider->setPosition(position.x, position.y);
}

void FirstSwordEntity::render(){
	myRenderManager->draw(mySprite, position.x, position.y, LayerInfo::swordLayer);
	myRenderManager->debugDrawRect(position.x, position.y, mySprite->getWidth(), mySprite->getHeight());
}

void FirstSwordEntity::onCollision(Entity* otherEntity){
}

int FirstSwordEntity::getDamage(){
	return damage;
}
