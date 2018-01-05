#pragma once
#include <vector>


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
				return e;
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
	const SDL_Point SELECTION_BOARD_POSITION = { 300, 300 };
	Sprite* selectedBoard;
	const SDL_Point SELECTED_BOARD_POSITION = { 150, 300 };
	Sprite* instructionText;
	const SDL_Point INSTRUCTION_TEXT_POSITION = { 100, 350 };
	Sprite* inventoryText;
	const SDL_Point INVENTORY_TEXT_POSITION = { 100, 200 };
	Sprite* selectedItemCursor;
	const SDL_Scancode leftKey = SDL_SCANCODE_A;
	const SDL_Scancode rightKey = SDL_SCANCODE_D;
};