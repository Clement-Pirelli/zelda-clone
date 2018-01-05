#pragma once

class PlayerAvatar;
class InventoryUI;
class HealthUI;
class MapUI;
class PlayerVariablesUI;

class UI {
public:
	UI(PlayerAvatar* givenPlayer);
	~UI();
	void render();
private:
	InventoryUI* myInventoryUI = nullptr;
	HealthUI* myHealthUI = nullptr;
	MapUI* myMapUI = nullptr;
	PlayerVariablesUI* myPlayerVariablesUI = nullptr;
};

