#pragma once
#include "RenderInfo.h"

class Inventory;
class Sprite;
class RenderManager;

class InventoryUI{
public:
	InventoryUI(Inventory* givenInventory);
	~InventoryUI();
	void render();
private:
	Inventory* myInventory;
	RenderManager* myRenderManager;
	Sprite* currentSwordItemSprite;
	Sprite* currentSecondItemSprite;
	Sprite* SwordItemBoxSprite;
	Sprite* SecondItemBoxSprite;
	const SDL_Point SECOND_ITEM_BOX_POSITION{ 300, 30 - RenderInfo::UI_HEIGHT};
	const SDL_Point SWORD_ITEM_BOX_POSITION{ SECOND_ITEM_BOX_POSITION.x + 50 , SECOND_ITEM_BOX_POSITION.y };
	const SDL_Point ITEM_BOX_DIMENSIONS{ 36,58 };
	const SDL_Point ITEM_OFFSET{ 2, 18 };
};