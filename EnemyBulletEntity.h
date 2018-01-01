#pragma once
#include "Entity.h"

class Sprite;
class RectangleCollider;
class RenderManager;

enum ENEMYDIRECTION;

class EnemyBulletEntity : public Entity{
public:
	EnemyBulletEntity(int givenX, int givenY, ENEMYDIRECTION givenDirection);
	~EnemyBulletEntity();
	void update(float givenDeltaTime);
	void render();
	Sprite* getSprite();
	Collider* getCollider();
	void onCollision(Entity* otherEntity);
	ENTITYTYPE getType();
	SDL_Point getPosition();
	SDL_Point getVelocity();
private:
	bool collidedWithPlayer = false;
	const int speed = 5;
	int velocityX = 0;
	int velocityY = 0;
	SDL_Point position;
	Sprite* mySprite = nullptr;
	RectangleCollider* myCollider = nullptr;
	RenderManager* myRenderManager = nullptr;
};

