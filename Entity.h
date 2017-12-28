#pragma once
#include <vector>

enum ENTITYTYPE {
	ENTITY_PLAYER,
	ENTITY_ENEMY,
	ENTITY_SWORD,
	ENTITY_OBSTACLE,
	ENTITY_HIDDEN_CAVE,
	ENTITY_TILE
};

class Sprite;
class Collider;

class Entity{
public:
	Entity(){};
	virtual ~Entity(){};
	virtual void update(float givenDeltaTime) = 0;
	virtual void render() = 0;
	virtual Sprite* getSprite() = 0;
	virtual Collider* getCollider() = 0;
	virtual void onCollision(Entity* otherEntity) = 0;
	virtual ENTITYTYPE getType() = 0;
};