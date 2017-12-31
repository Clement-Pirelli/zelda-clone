#pragma once
#include "Enemy.h"

enum SHSPRITEINDEX {
	PL_WALK_DOWN_ONE = 2,
	PL_WALK_DOWN_TWO = 3,
	PL_WALK_UP_ONE = 6,
	PL_WALK_UP_TWO = 7,
	PL_WALK_LEFT_ONE = 0,
	PL_WALK_LEFT_TWO = 1,
	PL_WALK_RIGHT_ONE = 4,
	PL_WALK_RIGHT_TWO = 5,
};

enum SHOOTINGENEMYSTATE {
	SH_SHOOTING,
	SH_WALKING,
	SH_WAITING_TO_WALK,
	SH_SPAWNING,
	SH_KNOCKED_BACK
};

class Animation;

class ShootingEnemy : public Enemy{
public:
	ShootingEnemy(int givenX, int givenY);
	~ShootingEnemy();
	void update(float givenDeltaTime) override;
	void render() override;
	void onCollision(Entity* otherEntity) override;
	Sprite* getSprite() override;
private:
	SHOOTINGENEMYSTATE state = SH_SPAWNING;
	Animation* walkingDownAnimation = nullptr,
		*walkingUpAnimation = nullptr,
		*walkingLeftAnimation = nullptr,
		*walkingRightAnimation = nullptr,
		*currentAnimation = nullptr;
	float movementAnimationTime = 0.3f;
	float timer = 0.0f;
	const float spawnTimer = 1.0f;
	const float walkTimer = 4.0f;
	int velocityX = 0;
	int velocityY = 0;
	ENEMYDIRECTION direction = ENEMYDIRECTION::E_UP;
	void chooseWalkingDirection();
};

