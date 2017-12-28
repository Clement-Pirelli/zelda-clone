#pragma once
#include "Entity.h"

class InputManager;
class RenderManager;
class RectangleCollider;

class BOTTOMTEXT_Entity : public Entity{
public:
	BOTTOMTEXT_Entity(SDL_Scancode givenLeftKey, SDL_Scancode givenRightKey, int givenX, int givenY);
	~BOTTOMTEXT_Entity();
	void update(float givenDeltaTime) override;
	void render() override;
	Sprite* getSprite() override;
	Collider* getCollider() override;
	void onCollision(Entity* otherEntity) override;
	ENTITYTYPE getType() override;
private:
	Sprite* mySprite = nullptr;
	InputManager* myInputManager = nullptr;
	RenderManager* myRenderManager = nullptr;
	SDL_Point position;
	int speed = 1;
	SDL_Scancode leftKey;
	SDL_Scancode rightKey;
	RectangleCollider* myCollider;
};

