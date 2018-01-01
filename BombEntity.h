#pragma once
#include "Entity.h"

class RectangleCollider;
class RenderManager;

class BombEntity : public Entity {
public:
	BombEntity(int givenX, int givenY);
	~BombEntity();
	void update(float givenDeltaTime) override;
	void render() override;
	Sprite* getSprite() override;
	Collider* getCollider() override;
	SDL_Point getPosition();
	void onCollision(Entity* otherEntity) override;
	ENTITYTYPE getType() override;
private:
	Sprite* mySprite = nullptr;
	RectangleCollider* myCollider = nullptr;
	RenderManager* myRenderManager;
	SDL_Point position;
	bool exploded = false;
	float timer = 0.0f;
	float deathTimer = 0.5f;
};

