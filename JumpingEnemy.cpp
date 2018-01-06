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
#include "Animation.h"
#include "SwordEntity.h"
#include "SwordProjectileEntity.h"
#include "EntityManager.h"

JumpingEnemy::JumpingEnemy(int givenX, int givenY){
	health = 3;
	damage = 1;
	speed = 3;
	jumpTimer = static_cast<float>(Utilities::random(1, 2)) / 2.5f;
	idleTimer = static_cast<float>(Utilities::random(1, 3)) / 2.5f;
	position.x = givenX;
	position.y = givenY;
	createAnimations();
	currentAnimation = idleAnimation;
	myCollider = new RectangleCollider(position.x, position.y, currentAnimation->getCurrentSprite()->getWidth(), currentAnimation->getCurrentSprite()->getHeight());
	Service<EntityManager>::getService()->addEntity(this);
}

JumpingEnemy::~JumpingEnemy(){
	Service<EntityManager>::getService()->removeEntity(this);
	delete myCollider;
	myCollider = nullptr;
	currentAnimation = nullptr;
	delete jumpingAnimation;
	jumpingAnimation = nullptr;
	delete idleAnimation;
	idleAnimation = nullptr;
}

void JumpingEnemy::update(float givenDeltaTime){
	switch (state){
	case JUMPINGENEMYSTATE::JM_SPAWNING:
		timer += givenDeltaTime;
		if (timer >= spawnTimer) {
			state = JUMPINGENEMYSTATE::JM_IDLE;
			timer = 0.0f;
		}
		break;
	case JUMPINGENEMYSTATE::JM_WAITING_TO_JUMP:
		velocity.x = Utilities::random(-speed, speed);
		velocity.y = Utilities::random(-speed, speed);
		currentAnimation = jumpingAnimation;
		state = JUMPINGENEMYSTATE::JM_JUMPING;
		break;
	case JUMPINGENEMYSTATE::JM_IDLE:
		currentAnimation = idleAnimation;
		timer += givenDeltaTime;
		if (timer >= idleTimer){
			if(Utilities::random(1, 4) > 2){
				state = JM_WAITING_TO_JUMP;
			}
			timer = 0.0f;
		}
		break;
	case JUMPINGENEMYSTATE::JM_JUMPING:
		position.x += velocity.x;
		position.y += velocity.y;
		timer += givenDeltaTime;
		if (timer >= jumpTimer){
			state = JUMPINGENEMYSTATE::JM_IDLE;
			timer = 0.0f;
		}
		break;
	case JUMPINGENEMYSTATE::JM_KNOCKED_BACK:
		position.x += velocity.x;
		position.y += velocity.y;
		timer += givenDeltaTime;
		if (timer >= knockbackTimer) {
			state = JUMPINGENEMYSTATE::JM_IDLE;
		}
		break;
	}
	if (position.x < 0
		|| position.x + currentAnimation->getCurrentSprite()->getWidth() > Service<RoomManager>::getService()->getCurrentRoom()->getWidthInPixels()
		|| position.y < 0
		|| position.y + currentAnimation->getCurrentSprite()->getHeight() > Service<RoomManager>::getService()->getCurrentRoom()->getHeightInPixels()
		){
		velocity.x *= -1;
		velocity.y *= -1;
	}
	myCollider->setPosition(position.x, position.y);
	currentAnimation->tick(givenDeltaTime);
	if (health <= 0) {
		spawnPickUp();
		Service<RoomManager>::getService()->getCurrentRoom()->decrementEnemyCount();
		delete this;
	}
	if (Service<RoomManager>::getService()->getRoomChange() == true){
		delete this;
	}
}

void JumpingEnemy::render(){
	if (state != JUMPINGENEMYSTATE::JM_SPAWNING){
		myRenderManager->draw(currentAnimation->getCurrentSprite(), position.x, position.y, LayerInfo::enemyLayer);
	}
}

void JumpingEnemy::onCollision(Entity* otherEntity){
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_SWORD && state != JUMPINGENEMYSTATE::JM_KNOCKED_BACK) {
		SwordEntity* sword = static_cast<SwordEntity*>(otherEntity);
		if (sword->getDirection() == SWORDDIRECTION::S_LEFT){
			setKnockback(-knockbackSpeed, 0, sword->getDamage());
		}
		if (sword->getDirection() == SWORDDIRECTION::S_RIGHT){
			setKnockback(knockbackSpeed, 0, sword->getDamage());
		}
		if (sword->getDirection() == SWORDDIRECTION::S_UP){
			setKnockback(0, -knockbackSpeed, sword->getDamage());
		}
		if (sword->getDirection() == SWORDDIRECTION::S_DOWN){
			setKnockback(0, knockbackSpeed, sword->getDamage());
		}
	}
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_PROJECTILE_SWORD && state != JUMPINGENEMYSTATE::JM_KNOCKED_BACK){
		SwordProjectileEntity* swordProjectile = static_cast<SwordProjectileEntity*>(otherEntity);
		if (swordProjectile->getVelocity().x > 0){
			setKnockback(knockbackSpeed, 0, swordProjectile->getDamage());
		}
		if (swordProjectile->getVelocity().x < 0){
			setKnockback(-knockbackSpeed, 0, swordProjectile->getDamage());
		}
		if (swordProjectile->getVelocity().y > 0){
			setKnockback(0, knockbackSpeed, swordProjectile->getDamage());
		}
		if (swordProjectile->getVelocity().y < 0){
			setKnockback(0, -knockbackSpeed, swordProjectile->getDamage());
		}
	}
}

Sprite* JumpingEnemy::getSprite(){
	return currentAnimation->getCurrentSprite();
}

void JumpingEnemy::createAnimations(){
	//idle
	{
		std::vector<Sprite*> tempSprites;
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/jumping_enemy.png", JMSPRITEINDEX::JM_JUMPINGINDEX * 30, 0, 32, 32));
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/jumping_enemy.png", JMSPRITEINDEX::JM_IDLEINDEX * 30, 0, 32, 32));
		idleAnimation= new Animation(tempSprites, idleAnimationTime);
	}
	//jumping
	{
		std::vector<Sprite*> tempSprites;
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/jumping_enemy.png", JMSPRITEINDEX::JM_JUMPINGINDEX * 30, 0, 32, 32));
		jumpingAnimation = new Animation(tempSprites, idleAnimationTime);
	}
}

void JumpingEnemy::setKnockback(int givenXKnockback, int givenYKnockback, int givenDamage){
	velocity.x = givenXKnockback;
	velocity.y = givenYKnockback;
	health -= givenDamage;
	timer = 0.0f;
	currentAnimation = jumpingAnimation;
	state = JUMPINGENEMYSTATE::JM_KNOCKED_BACK;
}
