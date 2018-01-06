#pragma once
#include "Entity.h"

class RectangleCollider;
class RenderManager;

class PickUp : public Entity{
public:
	PickUp(int givenX, int givenY);
	virtual ~PickUp();
	void onCollision(Entity* otherEntity) override;
	Collider* getCollider() override;
	SDL_Point getPosition() override;
	void render() override;
	virtual void update(float givenDeltaTime) override;
protected:
	RenderManager* myRenderManager = nullptr;
	SDL_Point position;
	bool pickedUp = false;
	RectangleCollider* myCollider = nullptr;
};