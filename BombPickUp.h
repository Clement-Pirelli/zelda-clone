#pragma once
#include "PickUp.h"
class BombPickUp : public PickUp{
public:
	BombPickUp(int givenX, int givenY);
	~BombPickUp();
	Sprite* getSprite() override;
	ENTITYTYPE getType() override;
private:
	Sprite* mySprite = nullptr;
};