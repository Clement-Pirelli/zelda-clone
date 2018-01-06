#include "stdafx.h"
#include "InventoryUI.h"
#include "Service.h"
#include "Inventory.h"
#include "InventoryItem.h"
#include "SwordItem.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"


InventoryUI::InventoryUI(Inventory* givenInventory){
	myInventory = givenInventory;
	myRenderManager = Service<RenderManager>::getService();
	SecondItemBoxSprite = Service<SpriteManager>::getService()->createSprite("../Assets/second_item_selection_UI.png", 0, 0, ITEM_BOX_DIMENSIONS.x, ITEM_BOX_DIMENSIONS.y);
	SwordItemBoxSprite = Service<SpriteManager>::getService()->createSprite("../Assets/sword_item_selection_UI.png", 0, 0, ITEM_BOX_DIMENSIONS.x, ITEM_BOX_DIMENSIONS.y);
}

InventoryUI::~InventoryUI(){
	delete SwordItemBoxSprite;
	SwordItemBoxSprite = nullptr;
	delete SecondItemBoxSprite;
	SecondItemBoxSprite = nullptr;
	myRenderManager = nullptr;
	myInventory = nullptr;
}

void InventoryUI::render(){
	if (myInventory->getItem() != nullptr){
		myRenderManager->draw(myInventory->getItem()->getDisplaySprite(), SECOND_ITEM_BOX_POSITION.x + ITEM_OFFSET.x, SECOND_ITEM_BOX_POSITION.y + ITEM_OFFSET.y);
	}
	if (myInventory->getSwordItem()->getDisplaySprite() != nullptr){
		myRenderManager->draw(myInventory->getSwordItem()->getDisplaySprite(), SWORD_ITEM_BOX_POSITION.x + ITEM_OFFSET.x, SWORD_ITEM_BOX_POSITION.y + ITEM_OFFSET.y);
	}
	myRenderManager->draw(SecondItemBoxSprite, SECOND_ITEM_BOX_POSITION.x, SECOND_ITEM_BOX_POSITION.y);
	myRenderManager->draw(SwordItemBoxSprite, SWORD_ITEM_BOX_POSITION.x, SWORD_ITEM_BOX_POSITION.y);
}
