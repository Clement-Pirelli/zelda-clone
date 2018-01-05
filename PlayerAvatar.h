#pragma once
#include "Entity.h"

enum PLAYERDIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum PLSPRITEINDEX {
	PL_WALK_DOWN_ONE = 0,
	PL_WALK_DOWN_TWO = 1,
	PL_WALK_UP_ONE = 2,
	PL_WALK_UP_TWO = 3,
	PL_WALK_HORIZONTAL_ONE = 4,
	PL_WALK_HORIZONTAL_TWO = 5,
	PL_ATTACK_DOWN = 6,
	PL_ATTACK_UP = 7,
	PL_ATTACK_HORIZONTAL = 8
};

enum PLAYERSTATE {
	PREPARING_TO_ATTACK,
	ATTACKING,
	MOVING,
	IDLE,
	KNOCKED_BACK
};

class InputManager;
class RenderManager;
class RectangleCollider;
class Animation;
class InventoryItem;
class SwordItem;
class Inventory;


class PlayerAvatar : public Entity{
public:
	PlayerAvatar(SDL_Scancode givenLeftKey, SDL_Scancode givenRightKey, SDL_Scancode givenUpKey, SDL_Scancode givenDownKey, SDL_Scancode givenSwordItemKey, SDL_Scancode givenSecondItemKey, int givenX, int givenY);
	~PlayerAvatar();
	void update(float givenDeltaTime) override;
	void render() override;
	void onCollision(Entity* otherEntity) override;
	Inventory* getInventory();
	SwordItem* getSwordItem();
	InventoryItem* getItem();
	Sprite* getSprite() override;
	Collider* getCollider() override;
	SDL_Point getPosition() override;
	ENTITYTYPE getType() override;
	PLAYERDIRECTION getDirection();
	int getHealth();
	int getMaxHealth();
	void addHealth(int givenHealth);
	void setPositionX(int givenPosition);
	void setPositionY(int givenPosition);
private:
	void createAnimations();
	void inputCheck();
	void setWalkingAnimation();
	void setAttackingAnimation();
	void setKnockback(int givenXKnockback, int givenYKnockback, int givenDamage);
	Animation* walkingDownAnimation = nullptr,
		*walkingUpAnimation = nullptr,
		*walkingHorizontallyAnimation = nullptr,
		*attackingDownAnimation = nullptr,
		*attackingUpAnimation = nullptr,
		*AttackingHorizontallyAnimation = nullptr,
		*currentAnimation = nullptr;
	InputManager* myInputManager = nullptr;
	RenderManager* myRenderManager = nullptr;
	RectangleCollider* myCollider = nullptr;
	Inventory* myInventory = nullptr;
	SDL_Scancode leftKey,
		rightKey,
		upKey,
		downKey,
		swordItemKey,
		secondItemKey;
	PLAYERDIRECTION direction = PLAYERDIRECTION::UP;
	PLAYERSTATE state = PLAYERSTATE::IDLE;
	SDL_Point position;
	SDL_Point lastPosition;
	SDL_Point velocity;
	bool hasBomb = true;
	int maxHalfHearts = 6;
	int halfHearts = maxHalfHearts;
	int rupeeCount = 0;
	int keyCount = 0;
	const int speed = 2;
	const int knockbackSpeed = 3;
	const float attackAnimationTime = 0.2f;
	const float movementAnimationTime = 0.2f;
	const float knockbackTime = 0.3f;
	float timer = 0.0f;
	//make this false until the player gets a bomb pick-up;
	
	

};