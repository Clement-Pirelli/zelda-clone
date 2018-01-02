#pragma once
#include "Entity.h"

enum ENEMYDIRECTION {
	E_UP,
	E_DOWN,
	E_LEFT,
	E_RIGHT
};

class RenderManager;
class RectangleCollider;
class Collider;

class Enemy : public Entity{
public:
	Enemy();
	virtual ~Enemy();
	int getDamage();
	Collider* getCollider() override;
	ENTITYTYPE getType() override;
	SDL_Point getPosition() override;
	SDL_Point getVelocity();
protected:
	SDL_Point position;
	SDL_Point velocity;
	RenderManager* myRenderManager = nullptr;
	RectangleCollider* myCollider = nullptr;
	//the unit for these variable is healf hearts
	int damage;
	int health;
};

