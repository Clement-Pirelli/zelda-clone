#pragma once
#include "PickUp.h"

class Animation;
class Sprite;

class FairyPickUp : public PickUp{
public:
	FairyPickUp(int givenX, int givenY);
	~FairyPickUp();
	void update(float givenDeltaTime) override;
	Sprite* getSprite() override;
	ENTITYTYPE getType() override;
private:
	float timer = 0.0f;
	const float deathTimer = 10.0f;
	Animation* myAnimation = nullptr;
	SDL_Point velocity;
};

