#include "stdafx.h"
#include "ShootingEnemy.h"
#include "RectangleCollider.h"
#include "Service.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "Animation.h"
#include "Sprite.h"
#include "EntityManager.h"
#include "LayerInfo.h"
#include "Utilities.h"
#include "RoomManager.h"
#include "Room.h"
#include "EnemyBulletEntity.h"
#include "SwordEntity.h"
#include "SwordProjectileEntity.h"

ShootingEnemy::ShootingEnemy(int givenX, int givenY){
	health = 2;
	damage = 1;
	Service<EntityManager>::getService()->addEntity(this);
	position.x = givenX;
	position.y = givenY;
	createAnimations();
	currentAnimation = walkingUpAnimation;
	myCollider = new RectangleCollider(position.x, position.y, currentAnimation->getCurrentSprite()->getWidth(), currentAnimation->getCurrentSprite()->getHeight());
}


ShootingEnemy::~ShootingEnemy(){
	delete myCollider;
	myCollider = nullptr;
	currentAnimation = nullptr;
	delete walkingRightAnimation;
	walkingRightAnimation = nullptr;
	delete walkingLeftAnimation;
	walkingLeftAnimation = nullptr;
	delete walkingUpAnimation;
	walkingUpAnimation = nullptr;
	delete walkingDownAnimation;
	walkingDownAnimation = nullptr;
	Service<EntityManager>::getService()->removeEntity(this);
}

void ShootingEnemy::update(float givenDeltaTime){
	lastPosition = position;
	switch (state) {
	case SHOOTINGENEMYSTATE::SH_SPAWNING:
		timer += givenDeltaTime;
		if (timer >= spawnTimer) {
			state = SHOOTINGENEMYSTATE::SH_WAITING_TO_WALK;
			timer = Utilities::random(0, 1);
		}
		break;
	case SHOOTINGENEMYSTATE::SH_WAITING_TO_WALK:
		chooseWalkingDirection();
		state = SHOOTINGENEMYSTATE::SH_WALKING;
		break;
	case SHOOTINGENEMYSTATE::SH_WALKING:
		position.x += velocity.x;
		position.y += velocity.y;
		timer += givenDeltaTime;
		if (timer >= spawnTimer) {
			int r = Utilities::random(1, 4);
			if (r > 1) {
				state = SH_WAITING_TO_WALK;
			} else {
				state = SH_WAITING_TO_SHOOT;
			}
			timer = 0.0f;
		}
		break;
	case SHOOTINGENEMYSTATE::SH_WAITING_TO_SHOOT:
		timer += givenDeltaTime;
		if (timer >= shootingWaitTimer) {
			state = SH_SHOOTING;
		}
		break;
	case SHOOTINGENEMYSTATE::SH_SHOOTING:
		new EnemyBulletEntity(position.x, position.y, direction);
		state = SHOOTINGENEMYSTATE::SH_WAITING_TO_WALK;
		break;
	case SHOOTINGENEMYSTATE::SH_KNOCKED_BACK:
		currentAnimation->setIfActive(false);
		position.x += velocity.x;
		position.y += velocity.y;
		timer += givenDeltaTime;
		if (timer >= knockbackTimer) {
			currentAnimation->setIfActive(true);
			state = SHOOTINGENEMYSTATE::SH_WAITING_TO_WALK;
		}
		break;
	}
	currentAnimation->tick(givenDeltaTime);
	if (position.x < 0
		|| position.x + currentAnimation->getCurrentSprite()->getWidth() > Service<RoomManager>::getService()->getCurrentRoom()->getWidthInPixels()
		|| position.y < 0
		|| position.y + currentAnimation->getCurrentSprite()->getHeight() > Service<RoomManager>::getService()->getCurrentRoom()->getHeightInPixels()
		){
		velocity.x *= -1;
		velocity.y *= -1;
	}
	myCollider->setPosition(position.x, position.y);

	if (health <= 0) {
		Service<RoomManager>::getService()->getCurrentRoom()->decrementEnemyCount();
		delete this;
	}
	if (Service<RoomManager>::getService()->getRoomChange() == true){
		delete this;
	}
}

void ShootingEnemy::render(){
	if (state != SHOOTINGENEMYSTATE::SH_SPAWNING) {
		myRenderManager->draw(currentAnimation->getCurrentSprite(), position.x, position.y, LayerInfo::enemyLayer);
	}
}

void ShootingEnemy::onCollision(Entity* otherEntity){
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_OBSTACLE || otherEntity->getType() == ENTITYTYPE::ENTITY_CAVE) {
		position = lastPosition;
	}
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_SWORD && state != SHOOTINGENEMYSTATE::SH_KNOCKED_BACK) {
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
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_PROJECTILE_SWORD && state != SHOOTINGENEMYSTATE::SH_KNOCKED_BACK){
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

Sprite* ShootingEnemy::getSprite(){
	return currentAnimation->getCurrentSprite();
}

void ShootingEnemy::chooseWalkingDirection(){
	int r = Utilities::random(1, 4);
	switch (r) {
	case 1:
		velocity.x = speed;
		velocity.y = 0;
		currentAnimation = walkingRightAnimation;
		direction = ENEMYDIRECTION::E_RIGHT;
		break;
	case 2:
		velocity.x = -speed;
		velocity.y = 0;
		currentAnimation = walkingLeftAnimation;
		direction = ENEMYDIRECTION::E_LEFT;
		break;
	case 3:
		velocity.y = speed;
		velocity.x = 0;
		currentAnimation = walkingDownAnimation;
		direction = ENEMYDIRECTION::E_DOWN;
		break;
	case 4:
		velocity.y = -speed;
		velocity.x = 0;
		currentAnimation = walkingUpAnimation;
		direction = ENEMYDIRECTION::E_UP;
		break;
	}
	timer = 0.0f;
}

void ShootingEnemy::setKnockback(int givenXKnockback, int givenYKnockback, int givenDamage){
	velocity.x = givenXKnockback;
	velocity.y = givenYKnockback;
	health -= givenDamage;
	timer = 0.0f;
	state = SHOOTINGENEMYSTATE::SH_KNOCKED_BACK;
}

void ShootingEnemy::createAnimations(){
	//walking down
	{
		std::vector<Sprite*> tempSprites;
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/shooting_enemy.png", SHSPRITEINDEX::PL_WALK_DOWN_ONE * 32, 0, 32, 32));
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/shooting_enemy.png", SHSPRITEINDEX::PL_WALK_DOWN_TWO * 32, 0, 32, 32));
		walkingDownAnimation = new Animation(tempSprites, movementAnimationTime);
	}
	//walking up
	{
		std::vector<Sprite*> tempSprites;
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/shooting_enemy.png", SHSPRITEINDEX::PL_WALK_UP_ONE * 32, 0, 32, 32));
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/shooting_enemy.png", SHSPRITEINDEX::PL_WALK_UP_TWO * 32, 0, 32, 32));
		walkingUpAnimation = new Animation(tempSprites, movementAnimationTime);
	}
	//walking left
	{
		std::vector<Sprite*> tempSprites;
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/shooting_enemy.png", SHSPRITEINDEX::PL_WALK_LEFT_ONE * 32, 0, 32, 32));
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/shooting_enemy.png", SHSPRITEINDEX::PL_WALK_LEFT_TWO * 32, 0, 32, 32));
		walkingLeftAnimation = new Animation(tempSprites, movementAnimationTime);
	}
	//walking right
	{
		std::vector<Sprite*> tempSprites;
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/shooting_enemy.png", SHSPRITEINDEX::PL_WALK_RIGHT_ONE * 32, 0, 32, 32));
		tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/shooting_enemy.png", SHSPRITEINDEX::PL_WALK_RIGHT_TWO * 32, 0, 32, 32));
		walkingRightAnimation = new Animation(tempSprites, movementAnimationTime);
	}
}
