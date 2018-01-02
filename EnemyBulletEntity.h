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
	int getDamage();
private:
	bool collidedWithPlayer = false;
	const int speed = 5;
	const int damage = 2;
	SDL_Point position;
	SDL_Point velocity;
	Sprite* mySprite = nullptr;
	RectangleCollider* myCollider = nullptr;
	RenderManager* myRenderManager = nullptr;
	std::string verticalSpriteFilePath = "../Assets/bullet.png";
	std::string horizontalSpriteFilePath = "../Assets/bullet_horizontal.png";
};

