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
	SDL_Point getPosition();
protected:
	SDL_Point position;
	RenderManager* myRenderManager = nullptr;
	RectangleCollider* myCollider = nullptr;
	//the unit for these variable is healf hearts
	int health = 2;
	int damage = 1;
	int speed = 1;
};

