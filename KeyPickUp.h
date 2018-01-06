#pragma once
#include "PickUp.h"

class Sprite;

class KeyPickUp : public PickUp{
public:
	KeyPickUp(int givenX, int givenY);
	~KeyPickUp();
	Sprite* getSprite() override;
	ENTITYTYPE getType() override;
private:
	Sprite* mySprite = nullptr;
};

