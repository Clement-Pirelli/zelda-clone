#pragma once

class PlayerAvatar;
class Sprite;

class InventoryItem{
public:
	InventoryItem(){};
	virtual ~InventoryItem(){};
	virtual void use(PlayerAvatar* givenPlayer) = 0;
	Sprite* getDisplaySprite(){ return displaySprite; };
protected:
	Sprite* displaySprite = nullptr;
	const int displaySpriteDimension = 32;
};