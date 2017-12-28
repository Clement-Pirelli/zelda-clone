#pragma once

class PlayerAvatar;

class InventoryItem{
public:
	InventoryItem(){};
	virtual ~InventoryItem(){};
	virtual void use(PlayerAvatar* givenPlayer) = 0;
};

