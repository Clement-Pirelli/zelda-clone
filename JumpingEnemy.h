#pragma once
#include "Enemy.h"

enum JMSPRITEINDEX {
	JM_JUMPINGINDEX = 0,
	JM_IDLEINDEX = 1,
};

enum JUMPINGENEMYSTATE {
	JM_JUMPING,
	JM_WAITING_TO_JUMP,
	JM_IDLE,
	JM_SPAWNING,
	JM_KNOCKED_BACK
};

class Sprite;
class Animation;

class JumpingEnemy : public Enemy{
public:
	JumpingEnemy(int givenX, int givenY);
	~JumpingEnemy();
	void update(float givenDeltaTime) override;
	void render() override;
	void onCollision(Entity* otherEntity) override;
	Sprite* getSprite() override;
private:
	void createAnimations();
	void setKnockback(int givenXKnockback, int givenYKnockback, int givenDamage);
	JUMPINGENEMYSTATE state = JUMPINGENEMYSTATE::JM_SPAWNING;
	Animation* idleAnimation;
	Animation* jumpingAnimation;
	Animation* currentAnimation;
	float timer = 0.0f;
	float jumpTimer = 1.0f;
	float idleTimer = 1.0f;
	const float spawnTimer = 2.0f;
	const float idleAnimationTime = 0.3f;
	const float knockbackTimer = 0.5f;
	int knockbackSpeed = 3;
};

