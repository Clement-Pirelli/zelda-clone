#pragma once
#include "RenderInfo.h"

class RoomManager;
class RenderManager;
class Sprite;

class MapUI{
public:
	MapUI();
	~MapUI();
	void render();
private:
	RenderManager* myRenderManager = nullptr;
	RoomManager* myRoomManager = nullptr;
	Sprite* roomCellSprite = nullptr;
	Sprite* currentRoomCellSprite = nullptr;
	const int roomCellDimension = 6;
	const SDL_Point MAP_POSITION{ 50, 50 - RenderInfo::UI_HEIGHT};
};

