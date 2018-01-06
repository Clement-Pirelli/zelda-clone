#pragma once
#include <vector>
#include "BombItem.h"
#include "RenderInfo.h"

class PlayerAvatar;
class InventoryItem;
class SwordItem;
class RenderManager;
class InputManager;
class Sprite;

class Inventory{
public:
	Inventory(PlayerAvatar* givenPlayer);
	~Inventory();
	InventoryItem* getItem();
	SwordItem* getSwordItem();
	void pushItem(InventoryItem* givenItem);
	void replaceSword(SwordItem* givenSword);
	void draw();
	void checkInput();
	template<typename T>
	T* getItem() {
		for (InventoryItem* e : items) {
			T* castPtr = dynamic_cast<T*>(e);
			if (castPtr != nullptr) {
				return static_cast<T*>(e);
			}
		}
		return nullptr;
	}
private:
	RenderManager* myRenderManager = nullptr;
	InputManager* myInputManager = nullptr;
	std::vector<InventoryItem*> items;
	SwordItem* swordItem;
	PlayerAvatar* player;
	int currentItem = 0;
	Sprite* selectionBoard;
	const SDL_Point SELECTION_BOARD_POSITION = { 300, 300 - RenderInfo::INVENTORY_HEIGHT };
	Sprite* selectedBoard;
	const SDL_Point SELECTED_BOARD_POSITION = { 150, SELECTION_BOARD_POSITION.y};
	Sprite* instructionText;
	const SDL_Point INSTRUCTION_TEXT_POSITION = { 100, 350 - RenderInfo::INVENTORY_HEIGHT };
	Sprite* inventoryText;
	const SDL_Point INVENTORY_TEXT_POSITION = { 100, 200 - RenderInfo::INVENTORY_HEIGHT };
	Sprite* selectedItemCursor;
	const SDL_Scancode leftKey = SDL_SCANCODE_A;
	const SDL_Scancode rightKey = SDL_SCANCODE_D;
};