#include "stdafx.h"
#include "Inventory.h"
#include "PlayerAvatar.h"
#include "Service.h"
#include "RenderManager.h"
#include "InventoryItem.h"
#include "LayerInfo.h"
#include "SwordItem.h"
#include "FirstSwordItem.h"
#include "InputManager.h"
#include "Sprite.h"
#include "SpriteManager.h"


Inventory::Inventory(PlayerAvatar* givenPlayer){
	player = givenPlayer;
	swordItem = new FirstSwordItem();
	myRenderManager = Service<RenderManager>::getService();
	myInputManager = Service<InputManager>::getService();
	instructionText = Service<SpriteManager>::getService()->createSprite("../Assets/instruction_text_UI.png", 0, 0, 158, 34);
	selectedBoard = Service<SpriteManager>::getService()->createSprite("../Assets/selected_item_board_UI.png", 0, 0, 42, 42);
	selectionBoard = Service<SpriteManager>::getService()->createSprite("../Assets/item_board_UI.png", 0, 0, 196, 84);
	inventoryText = Service<SpriteManager>::getService()->createSprite("../Assets/inventory_text_UI.png", 0, 0, 138, 14);
	selectedItemCursor = Service<SpriteManager>::getService()->createSprite("../Assets/selection_cursor_UI.png", 0, 0, 32, 32);
}


Inventory::~Inventory(){
	myInputManager = nullptr;
	myRenderManager = nullptr;
	delete swordItem;
	swordItem = nullptr;
	player = nullptr;
}

InventoryItem* Inventory::getItem(){
	if (items.size() != 0){
		return items[currentItem];
	}
	return nullptr;
}

SwordItem* Inventory::getSwordItem(){
	return swordItem;
}

void Inventory::pushItem(InventoryItem* givenItem){
	items.push_back(givenItem);
}

void Inventory::replaceSword(SwordItem* givenSword){
	delete swordItem;
	swordItem = givenSword;
}

void Inventory::draw(){
	for (unsigned int i = 0; i < items.size(); i++){
		myRenderManager->draw(items[i]->getDisplaySprite(), SELECTION_BOARD_POSITION.x + 16 * i, SELECTION_BOARD_POSITION.y);
	}
	myRenderManager->draw(inventoryText, INVENTORY_TEXT_POSITION.x, INVENTORY_TEXT_POSITION.y);
	myRenderManager->draw(inventoryText, INVENTORY_TEXT_POSITION.x, INVENTORY_TEXT_POSITION.y);
	myRenderManager->draw(instructionText, INSTRUCTION_TEXT_POSITION.x, INSTRUCTION_TEXT_POSITION.y);
	myRenderManager->draw(selectedBoard, SELECTED_BOARD_POSITION.x, SELECTED_BOARD_POSITION.y);
	myRenderManager->draw(selectionBoard, SELECTION_BOARD_POSITION.x, SELECTION_BOARD_POSITION.y);
	if (items.size() != 0){
		myRenderManager->draw(items[currentItem]->getDisplaySprite(), SELECTED_BOARD_POSITION.x + 3, SELECTED_BOARD_POSITION.y + 3);
	}
	myRenderManager->draw(selectedItemCursor, SELECTION_BOARD_POSITION.x + 3 + currentItem * 32, SELECTION_BOARD_POSITION.y + 3);
}

void Inventory::checkInput(){
	if(items.size() != 0){
		if (myInputManager->isKeyPressed(leftKey)) {
			currentItem--;
			if (currentItem < 0){
				currentItem = static_cast<int>(items.size()) - 1;
			}
		} else {
			if (myInputManager->isKeyPressed(rightKey)){
				currentItem++;
				if (currentItem >= items.size()){
					currentItem = static_cast<int>(items.size()) - 1;
				}
			}
		}
	}
}
