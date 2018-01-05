#pragma once

class Inventory;

class InventoryUI{
public:
	InventoryUI(Inventory* givenInventory);
	~InventoryUI();
	void render();
private:
	Inventory* myInventory;
};

