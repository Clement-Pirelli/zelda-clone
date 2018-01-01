#pragma once
#include "Entity.h"

class Sprite;
class RectangleCollider;
class RenderManager;
class FirstSwordEntity;

class SwordProjectileEntity : public Entity{
public:
	SwordProjectileEntity(FirstSwordEntity* givenSword);
	~SwordProjectileEntity();
	void update(float givenDeltaTime) override;
	void render() override;
	Sprite* getSprite() override;
	Collider* getCollider() override;
	void onCollision(Entity* otherEntity) override;
	ENTITYTYPE getType() override;
	SDL_Point getPosition() override;
private:
	Sprite* mySprite = nullptr;
	RectangleCollider* myCollider = nullptr;
	RenderManager* myRenderManager;
	SDL_Point position;
	SDL_Point velocity{ 0,0 };
	const int speed = 4;
};

