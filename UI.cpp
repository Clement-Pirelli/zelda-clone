#include "stdafx.h"
#include "UI.h"
#include "InventoryUI.h"
#include "MapUI.h"
#include "HealthUI.h"
#include "PlayerVariablesUI.h"
#include "PlayerAvatar.h"

UI::UI(PlayerAvatar* givenPlayer){
	myInventoryUI = new InventoryUI(givenPlayer->getInventory());
	myHealthUI = new HealthUI(givenPlayer);
	myMapUI = new MapUI();
	myPlayerVariablesUI = new PlayerVariablesUI(givenPlayer);
}


UI::~UI(){
	delete myPlayerVariablesUI;
	myPlayerVariablesUI = nullptr;
	delete myMapUI;
	myMapUI = nullptr;
	delete myHealthUI;
	myHealthUI = nullptr;
	delete myInventoryUI;
	myInventoryUI = nullptr;
}

void UI::render(){
	myInventoryUI->render();
	myHealthUI->render();
	myMapUI->render();
	myPlayerVariablesUI->render();
}
