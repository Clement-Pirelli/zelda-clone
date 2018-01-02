#include "stdafx.h"
#include "JumpingEnemy.h"
#include "Service.h"
#include "RectangleCollider.h"
#include "RenderManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "LayerInfo.h"
#include "RoomManager.h"
#include "Room.h"
#include "Utilities.h"

JumpingEnemy::JumpingEnemy(int givenX, int givenY){
	position.x = givenX;
	position.y = givenY;
	jumpingSprite = Service<SpriteManager>::getService()->createSprite("../Assets/jumping_enemy.png", JMSPRITEINDEX::JM_JUMPING * 32, 0, 32, 32);
	idleSprite = Service<SpriteManager>::getService()->createSprite("../Assets/jumping_enemy.png", JMSPRITEINDEX::JM_IDLE * 32, 0, 32, 32);
	currentSprite = idleSprite;
	myRenderManager = Service<RenderManager>::getService();
	myCollider = new RectangleCollider(position.x, position.y, currentSprite->getWidth(), currentSprite->getHeight());
}


JumpingEnemy::~JumpingEnemy(){
	delete myCollider;
	myCollider = nullptr;
	myRenderManager = nullptr;
	currentSprite = nullptr;
	idleSprite = nullptr;
	jumpingSprite = nullptr;
}

void JumpingEnemy::update(float givenDeltaTime){
	switch (state){
	case JUMPINGENEMYSTATE::JM_SPAWNING:
		timer += givenDeltaTime;
		if (timer >= spawnTimer) {
			state = JUMPINGENEMYSTATE::JM_WAITING_TO_JUMP;
			timer = Utilities::random(0, 1);
		}
		break;
	}
	if (position.x < 0
		|| position.x + currentSprite->getWidth() > Service<RoomManager>::getService()->getCurrentRoom()->getWidthInPixels()
		|| position.y < 0
		|| position.y + currentSprite->getHeight() > Service<RoomManager>::getService()->getCurrentRoom()->getHeightInPixels()
		){
		velocity.x *= -1;
		velocity.y *= -1;
	}
	myCollider->setPosition(position.x, position.y);
}

void JumpingEnemy::render(){
	if (state != JUMPINGENEMYSTATE::JM_SPAWNING){
		myRenderManager->draw(currentSprite, position.x, position.y, LayerInfo::enemyLayer);
	}
}

void JumpingEnemy::onCollision(Entity* otherEntity){
}

Sprite* JumpingEnemy::getSprite(){
	return nullptr;
}
