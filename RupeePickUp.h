#pragma once
#include "PickUp.h"

class Animation;

class RupeePickUp : public PickUp{
public:
	RupeePickUp(int givenX, int givenY);
	~RupeePickUp();
	void update(float givenDeltaTime) override;
	Sprite* getSprite() override;
	ENTITYTYPE getType() override;
private:
	Animation* myAnimation = nullptr;
};

