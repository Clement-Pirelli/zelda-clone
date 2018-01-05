#include "stdafx.h"
#include "InventoryUI.h"


InventoryUI::InventoryUI(Inventory* givenInventory){
	myInventory = givenInventory;
}


InventoryUI::~InventoryUI(){
	myInventory = nullptr;
}

void InventoryUI::render(){
}
