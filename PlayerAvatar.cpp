#include "stdafx.h"
#include "PlayerAvatar.h"
#include "Service.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Animation.h"
#include "RectangleCollider.h"
#include "InventoryItem.h"
#include "FirstSwordItem.h"
#include "BombItem.h"
#include "LayerInfo.h"
#include "Room.h"
#include <vector>


PlayerAvatar::PlayerAvatar(SDL_Scancode givenLeftKey, SDL_Scancode givenRightKey, SDL_Scancode givenUpKey, SDL_Scancode givenDownKey, SDL_Scancode givenSwordItemKey, SDL_Scancode givenSecondItemKey, int givenX, int givenY) {
	leftKey = givenLeftKey;
	rightKey = givenRightKey;
	upKey = givenUpKey;
	downKey = givenDownKey;
	swordItemKey = givenSwordItemKey;
	secondItemKey = givenSecondItemKey;
	position.x = givenX;
	position.y = givenY;
	//animation creation
	{
		//walking down
		{
			std::vector<Sprite*> tempSprites;
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_WALK_DOWN_ONE * 32, 0, 32, 32));
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_WALK_DOWN_TWO * 32, 0, 32, 32));
			walkingDownAnimation = new Animation(tempSprites, movementAnimationTime);
		}
		//walking up
		{
			std::vector<Sprite*> tempSprites;
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_WALK_UP_ONE * 32, 0, 32, 32));
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_WALK_UP_TWO * 32, 0, 32, 32));
			walkingUpAnimation = new Animation(tempSprites, movementAnimationTime);
		}
		//walking horizontally
		{
			std::vector<Sprite*> tempSprites;
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_WALK_HORIZONTAL_ONE * 32, 0, 32, 32));
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_WALK_HORIZONTAL_TWO * 32, 0, 32, 32));
			walkingHorizontallyAnimation = new Animation(tempSprites, movementAnimationTime);
		}
		//attacking down
		{
			std::vector<Sprite*> tempSprites;
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_ATTACK_DOWN * 32, 0, 32, 32));
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_ATTACK_DOWN * 32, 0, 32, 32));
			attackingDownAnimation = new Animation(tempSprites, attackAnimationTime);
		}
		//attacking up
		{
			std::vector<Sprite*> tempSprites;
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_ATTACK_UP * 32, 0, 32, 32));
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_ATTACK_UP * 32, 0, 32, 32));
			attackingUpAnimation = new Animation(tempSprites, attackAnimationTime);
		}
		//attacking horizontally
		{
			std::vector<Sprite*> tempSprites;
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_ATTACK_HORIZONTAL * 32, 0, 32, 32));
			tempSprites.push_back(Service<SpriteManager>::getService()->createSprite("../Assets/link.png", PLSPRITEINDEX::PL_ATTACK_HORIZONTAL * 32, 0, 32, 32));
			AttackingHorizontallyAnimation = new Animation(tempSprites, attackAnimationTime);
		}
	}
	currentAnimation = walkingDownAnimation;
	direction = PLAYERDIRECTION::DOWN;
	myInputManager = Service<InputManager>::getService();
	myRenderManager = Service<RenderManager>::getService();
	myCollider = new RectangleCollider(position.x, position.y, getSprite()->getWidth(), getSprite()->getHeight());
	swordItem = new FirstSwordItem();
	//TODO : change this to make it be chosen in the inventory
	secondItem = new BombItem();
}

PlayerAvatar::~PlayerAvatar(){
	//delete every animation
	currentAnimation = nullptr;
	delete myCollider;
	myCollider = nullptr;
	delete walkingDownAnimation;
	walkingDownAnimation = nullptr;
	delete walkingUpAnimation;
	walkingUpAnimation = nullptr;
	delete walkingHorizontallyAnimation;
	walkingHorizontallyAnimation = nullptr;
	delete attackingDownAnimation;
	attackingDownAnimation = nullptr;
	delete attackingUpAnimation;
	attackingUpAnimation = nullptr;
	delete AttackingHorizontallyAnimation;
	AttackingHorizontallyAnimation = nullptr;
	//When the inventory system is done, these will not be deleted here!
	delete swordItem;
	swordItem = nullptr;
	delete secondItem;
	secondItem = nullptr;
}

void PlayerAvatar::update(float givenDeltaTime) {
	lastPosition.x = position.x;
	lastPosition.y = position.y;
	velocityX = 0;
	velocityY = 0;
	switch (state) {
	case PLAYERSTATE::IDLE:
		//set animation as idle
		//check for input
		currentAnimation->setIfActive(false);
		inputCheck();
		position.x += velocityX;
		position.y += velocityY;
		break;
	case PLAYERSTATE::PREPARING_TO_ATTACK:
		//spawn the sword
		swordItem->use(this);
		//set the animation to attacking
		currentAnimation->setIfActive(true);
		setAttackingAnimation();
		state = PLAYERSTATE::ATTACKING;
		break;
	case PLAYERSTATE::ATTACKING:
		//set the state to idle when the animation is over
		timer += givenDeltaTime;
		if (timer >= attackAnimationTime * 2) {
			//if full health, then spawn a projectile sword
			if (halfHearts == maxHalfHearts) {
				swordItem->useFullHealth();
			}
			//stop using the sword
			swordItem->stopUse();
			//set the animation back to a walking animation, in case the attack animation hasn't ended yet
			setWalkingAnimation();
			state = PLAYERSTATE::IDLE;
			timer = 0.0f;
		}
		break;
	case PLAYERSTATE::MOVING:
		//check for input, set the animation according to input, set the speed according to input
		inputCheck();
		currentAnimation->setIfActive(true);
		setWalkingAnimation();
		position.x += velocityX;
		position.y += velocityY;
		if (velocityX == 0 && velocityY == 0) {
			state = PLAYERSTATE::IDLE;
		}
		break;
	case PLAYERSTATE::KNOCKED_BACK:
		currentAnimation->setIfActive(false);
		position.x += velocityX;
		position.y += velocityY;
		timer += givenDeltaTime;
		if (timer >= knockBackTime) {
			state = PLAYERSTATE::IDLE;
			timer = 0.0f;
		}
		break;
	}
	myCollider->setPosition(position.x, position.y);
	currentAnimation->tick(givenDeltaTime);
}

void PlayerAvatar::render(){
	myRenderManager->draw(currentAnimation->getCurrentSprite(), position.x, position.y, LayerInfo::playerLayer);
	myRenderManager->debugDrawRect(myCollider->getRectangle());
}

Sprite* PlayerAvatar::getSprite(){
	return currentAnimation->getCurrentSprite();
}

Collider* PlayerAvatar::getCollider(){
	return myCollider;
}

SDL_Point PlayerAvatar::getPosition(){
	return position;
}

void PlayerAvatar::onCollision(Entity* otherEntity){
	if (otherEntity->getType() == ENTITYTYPE::ENTITY_CAVE) {
		position.x = Room::getWidthInPixels() / 2;
		position.y = Room::getHeightInPixels() - getSprite()->getHeight();
	} else {
		if (otherEntity->getType() == ENTITYTYPE::ENTITY_OBSTACLE) {
			position.x = lastPosition.x;
			position.y = lastPosition.y;
			myCollider->setPosition(position.x, position.y);
		}
	}
	
	
}

ENTITYTYPE PlayerAvatar::getType(){
	return ENTITYTYPE::ENTITY_PLAYER;
}

PLAYERDIRECTION PlayerAvatar::getDirection(){
	return direction;
}

int PlayerAvatar::getHealth(){
	return halfHearts;
}

int PlayerAvatar::getMaxHealth(){
	return maxHalfHearts;
}

void PlayerAvatar::addHealth(int givenHealth){
	halfHearts += givenHealth;
}

void PlayerAvatar::setPositionX(int givenPosition){
	position.x = givenPosition;
}

void PlayerAvatar::setPositionY(int givenPosition){
	position.y = givenPosition;
}

void PlayerAvatar::inputCheck(){
	if (myInputManager->isKeyDown(swordItemKey)) {
		state = PLAYERSTATE::PREPARING_TO_ATTACK;
	} else {
		if (myInputManager->isKeyPressed(secondItemKey)) {
			secondItem->use(this);
		} else {
			if (myInputManager->isKeyDown(leftKey)) {
				velocityX = -speed;
				direction = PLAYERDIRECTION::LEFT;
				state = PLAYERSTATE::MOVING;
			} else {
				if (myInputManager->isKeyDown(rightKey)) {
					velocityX = speed;
					direction = PLAYERDIRECTION::RIGHT;
					state = PLAYERSTATE::MOVING;
				} else {
					if (myInputManager->isKeyDown(upKey)) {
						velocityY = -speed;
						direction = PLAYERDIRECTION::UP;
						state = PLAYERSTATE::MOVING;
					} else {
						if (myInputManager->isKeyDown(downKey)) {
							velocityY = speed;
							direction = PLAYERDIRECTION::DOWN;
							state = PLAYERSTATE::MOVING;
						}
					}
				}
			}
		}
		
	}
}

void PlayerAvatar::setWalkingAnimation(){
	switch (direction) {
	case PLAYERDIRECTION::UP:
		currentAnimation = walkingUpAnimation;
		break;
	case PLAYERDIRECTION::DOWN:
		currentAnimation = walkingDownAnimation;
		break;
	case PLAYERDIRECTION::LEFT:
		currentAnimation = walkingHorizontallyAnimation;
		currentAnimation->setFlip(SDL_FLIP_HORIZONTAL);
		break;
	case PLAYERDIRECTION::RIGHT:
		currentAnimation = walkingHorizontallyAnimation;
		currentAnimation->setFlip(SDL_FLIP_NONE);
		break;
	}
}

void PlayerAvatar::setAttackingAnimation(){
	switch (direction) {
	case PLAYERDIRECTION::UP:
		currentAnimation = attackingUpAnimation;
		break;
	case PLAYERDIRECTION::DOWN:
		currentAnimation = attackingDownAnimation;
		break;
	case PLAYERDIRECTION::LEFT:
		currentAnimation = AttackingHorizontallyAnimation;
		currentAnimation->setFlip(SDL_FLIP_HORIZONTAL);
		break;
	case PLAYERDIRECTION::RIGHT:
		currentAnimation = AttackingHorizontallyAnimation;
		currentAnimation->setFlip(SDL_FLIP_NONE);
		break;
	}
}