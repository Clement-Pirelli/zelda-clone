#pragma once
#include "PickUp.h"

class Sprite;

class HeartPickUp : public PickUp{
public:
	HeartPickUp(int givenX, int givenY);
	~HeartPickUp();
	Sprite* getSprite() override;
	ENTITYTYPE getType() override;
private:
	Sprite* mySprite = nullptr;
};