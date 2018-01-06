#pragma once
#include "Room.h"

namespace RenderInfo{
	const int UI_HEIGHT = 140;
	const int GAME_HEIGHT = Room::getHeightInPixels();
	const int INVENTORY_HEIGHT = UI_HEIGHT + GAME_HEIGHT;
}