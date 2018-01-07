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
	secondItemBoxSprite = Service<SpriteManager>::getService()->createSprite("../Assets/second_item_selection_UI.png", 0, 0, ITEM_BOX_DIMENSIONS.x, ITEM_BOX_DIMENSIONS.y);
	swordItemBoxSprite = Service<SpriteManager>::getService()->createSprite("../Assets/sword_item_selection_UI.png", 0, 0, ITEM_BOX_DIMENSIONS.x, ITEM_BOX_DIMENSIONS.y);
}

InventoryUI::~InventoryUI(){
	Service<SpriteManager>::getService()->destroySprite(swordItemBoxSprite);
	swordItemBoxSprite = nullptr;
	Service<SpriteManager>::getService()->destroySprite(secondItemBoxSprite);
	secondItemBoxSprite = nullptr;
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
	myRenderManager->draw(secondItemBoxSprite, SECOND_ITEM_BOX_POSITION.x, SECOND_ITEM_BOX_POSITION.y);
	myRenderManager->draw(swordItemBoxSprite, SWORD_ITEM_BOX_POSITION.x, SWORD_ITEM_BOX_POSITION.y);
}
