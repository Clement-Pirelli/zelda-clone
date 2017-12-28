#pragma once
#include "Entity.h"

enum PLAYERDIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHT
};
enum SPRITEINDEX {
	WALK_DOWN_ONE = 0,
	WALK_DOWN_TWO = 1,
	WALK_UP_ONE = 2,
	WALK_UP_TWO = 3,
	WALK_HORIZONTAL_ONE = 4,
	WALK_HORIZONTAL_TWO = 5,
	ATTACK_DOWN = 6,
	ATTACK_UP = 7,
	ATTACK_HORIZONTAL = 8
};
enum PLAYERSTATE {
	PREPARING_TO_ATTACK,
	ATTACKING,
	MOVING,
	IDLE
};

class InputManager;
class RenderManager;
class RectangleCollider;
class Animation;
class InventoryItem;
class SwordItem;


class PlayerAvatar : public Entity{
public:
	PlayerAvatar(SDL_Scancode givenLeftKey, SDL_Scancode givenRightKey, SDL_Scancode givenUpKey, SDL_Scancode givenDownKey, SDL_Scancode givenSwordItemKey, int givenX, int givenY);
	~PlayerAvatar();
	void update(float givenDeltaTime) override;
	void render() override;
	void onCollision(Entity* otherEntity) override;
	Sprite* getSprite() override;
	Collider* getCollider() override;
	SDL_Point getPosition();
	ENTITYTYPE getType() override;
	PLAYERDIRECTION getDirection();
	int getHealth();
	int getMaxHealth();
	void addHealth(int givenHealth);
	void setPositionX(int givenPosition);
	void setPositionY(int givenPosition);
private:
	void inputCheck();
	void setWalkingAnimation();
	void setAttackingAnimation();
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
	SwordItem* swordItem = nullptr;
	InventoryItem* secondItem = nullptr;
	SDL_Scancode leftKey,
		rightKey,
		upKey,
		downKey,
		swordItemKey;
	PLAYERDIRECTION direction = PLAYERDIRECTION::UP;
	PLAYERSTATE state = PLAYERSTATE::IDLE;
	static const ENTITYTYPE type = ENTITYTYPE::ENTITY_PLAYER;
	SDL_Point position;
	int velocityX = 0;
	int velocityY = 0;
	int halfHearts = 6;
	int maxHalfHearts = 6;
	const int speed = 2;
	const float attackAnimationTime = 0.2f;
	const float movementAnimationTime = 0.2f;
	float attackTimer = 0.0f;
};