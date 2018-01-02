#pragma once
#include "Enemy.h"

enum JMSPRITEINDEX {
	JM_JUMPING = 0,
	JM_IDLE = 1,
};

enum JUMPINGENEMYSTATE {
	JM_JUMPING,
	JM_WAITING_TO_JUMP,
	JM_SPAWNING,
	JM_KNOCKED_BACK
};

class JumpingEnemy : public Enemy{
public:
	JumpingEnemy(int givenX, int givenY);
	~JumpingEnemy();
	void update(float givenDeltaTime) override;
	void render() override;
	void onCollision(Entity* otherEntity) override;
	Sprite* getSprite() override;
private:
	JUMPINGENEMYSTATE state = JUMPINGENEMYSTATE::JM_SPAWNING;
	Sprite* currentSprite = nullptr;
	Sprite* jumpingSprite = nullptr;
	Sprite* idleSprite = nullptr;
	float timer = 0.0f;
	const float spawnTimer = 2.0f;
};

