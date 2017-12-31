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

ShootingEnemy::ShootingEnemy(int givenX, int givenY){
	Service<EntityManager>::getService()->addEntity(this);
	position.x = givenX;
	position.y = givenY;
	//animation creation
	{
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
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/shooting_enemy.png", SHSPRITEINDEX::PL_WALK_UP_ONE * 32, 0, 32, 32));
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
	if (health <= 0) {
		Service<RoomManager>::getService()->getCurrentRoom()->decrementEnemyCount();
		delete this;
	}
	switch (state) {
	case SHOOTINGENEMYSTATE::SH_SPAWNING:
		timer += givenDeltaTime;
		if (timer >= spawnTimer) {
			state = SH_WAITING_TO_WALK;
			timer = 0.0f;
		}
		break;
	case SHOOTINGENEMYSTATE::SH_WAITING_TO_WALK:
		velocityX = 0;
		velocityY = 0;
		chooseWalkingDirection();
		break;
	case SHOOTINGENEMYSTATE::SH_WALKING:
		position.x += velocityX;
		position.y += velocityY;
		timer += givenDeltaTime;
		if (timer >= spawnTimer) {
			int r = Utilities::random(1, 2);
			if (r == 1) {
				state = SH_WAITING_TO_WALK;
			} else {
				state = SH_SHOOTING;
			}
			timer = 0.0f;
		}
		break;
	case SHOOTINGENEMYSTATE::SH_SHOOTING:
		
		break;
	case SHOOTINGENEMYSTATE::SH_KNOCKED_BACK:
		break;
	}
	currentAnimation->tick(givenDeltaTime);
	myCollider->setPosition(position.x, position.y);
}

void ShootingEnemy::render(){
	if (state != SHOOTINGENEMYSTATE::SH_SPAWNING) {
		myRenderManager->draw(currentAnimation->getCurrentSprite(), position.x, position.y, LayerInfo::enemyLayer);
	}
}

void ShootingEnemy::onCollision(Entity* otherEntity){
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_OBSTACLE || otherEntity->getType() == ENTITYTYPE::ENTITY_CAVE) {

	}
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_SWORD) {
		if (state != SHOOTINGENEMYSTATE::SH_KNOCKED_BACK) {
			health--;
			timer = 0.0f;
			state = SHOOTINGENEMYSTATE::SH_KNOCKED_BACK;
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
		velocityX = speed;
		currentAnimation = walkingRightAnimation;
		direction = ENEMYDIRECTION::E_RIGHT;
		break;
	case 2:
		velocityX = -speed;
		currentAnimation = walkingLeftAnimation;
		direction = ENEMYDIRECTION::E_LEFT;
		break;
	case 3:
		velocityY = speed;
		currentAnimation = walkingDownAnimation;
		direction = ENEMYDIRECTION::E_DOWN;
		break;
	case 4:
		velocityY = -speed;
		currentAnimation = walkingUpAnimation;
		direction = ENEMYDIRECTION::E_UP;
		break;
	}
	state = SHOOTINGENEMYSTATE::SH_WALKING;
}
