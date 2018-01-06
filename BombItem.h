#pragma once
#include "InventoryItem.h"

class BombEntity;

class BombItem : public InventoryItem{
public:
	BombItem();
	~BombItem();
	void use(PlayerAvatar* givenPlayer) override;
	int getBombCount();
	void addBomb();
private:
	int bombCount = 1;
};

