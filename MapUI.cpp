#include "stdafx.h"
#include "MapUI.h"
#include "Service.h"
#include "RoomManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "RenderManager.h"

MapUI::MapUI(){
	myRenderManager = Service<RenderManager>::getService();
	myRoomManager = Service<RoomManager>::getService();
	roomCellSprite = Service<SpriteManager>::getService()->createSprite("../Assets/map_room_UI.png", 0, 0, roomCellDimension, roomCellDimension);
	currentRoomCellSprite = Service<SpriteManager>::getService()->createSprite("../Assets/map_current_room_UI.png", 0, 0, roomCellDimension, roomCellDimension);
}


MapUI::~MapUI(){
	Service<SpriteManager>::getService()->destroySprite(currentRoomCellSprite);
	currentRoomCellSprite = nullptr;
	Service<SpriteManager>::getService()->destroySprite(roomCellSprite);
	roomCellSprite = nullptr;
	myRoomManager = nullptr;
	myRenderManager = nullptr;
}

void MapUI::render(){
	for (unsigned int i = 0; i < RoomManager::maxRow; i++){
		for (unsigned int j = 0; j < RoomManager::maxColumn; j++){
			myRenderManager->draw(roomCellSprite, MAP_POSITION.x + i * roomCellDimension, MAP_POSITION.y + j * roomCellDimension);
		}
	}
	myRenderManager->draw(currentRoomCellSprite, MAP_POSITION.x + myRoomManager->getCurrentRow() * roomCellDimension, MAP_POSITION.y + myRoomManager->getCurrentColumn() * roomCellDimension, 2);
}
