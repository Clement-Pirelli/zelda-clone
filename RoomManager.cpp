#include "stdafx.h"
#include "RoomManager.h"
#include "Room.h"
#include "Service.h"
#include "EntityManager.h"
#include "PlayerAvatar.h"
#include "Sprite.h"
#include "SwordProjectileEntity.h"
#include <vector>

RoomManager::RoomManager(){
	for (unsigned int i = 0; i < RoomManager::maxRow; i++) {
		for (unsigned int j = 0; j < RoomManager::maxColumn; j++) {
			roomArray[i][j] = nullptr;
		}
	}
}


RoomManager::~RoomManager(){
	for (unsigned int i = 0; i < RoomManager::maxRow; i++) {
		for (unsigned int j = 0; j < RoomManager::maxColumn; j++) {
			if (roomArray[i][j] != nullptr) {
				delete roomArray[i][j];
				roomArray[i][j] = nullptr;
			}
		}
	}
}

Room* RoomManager::getCurrentRoom(){
	return roomArray[currentRow][currentColumn];
}

bool RoomManager::getRoomChange(){
	return roomChange;
}

void RoomManager::update(){
	roomChange = false;
	std::vector<PlayerAvatar*> players = Service<EntityManager>::getService()->getEntities<PlayerAvatar>();
	//This assumes that the player cannot go out of bounds, aka that the level design is sound.
	for (PlayerAvatar* pl : players) {
		if (pl->getPosition().x > Room::getWidthInPixels() - pl->getSprite()->getWidth()) {
			if (roomArray[currentRow][currentColumn]->getSpecialDestination().x == -1) {
				changeRoom(currentRow, currentColumn + 1);
				pl->setPositionX(0);
				
			}
			else {
				changeRoom(roomArray[currentRow][currentColumn]->getSpecialDestination().x, roomArray[currentRow][currentColumn]->getSpecialDestination().y);
				//TODO : implement caves
			}
			roomChange = true;
		}
		if (pl->getPosition().x < 0) {
			changeRoom(currentRow, currentColumn - 1);
			pl->setPositionX(Room::getWidthInPixels() - pl->getSprite()->getWidth());
			std::vector<SwordProjectileEntity*> projectiles = Service<EntityManager>::getService()->getEntities<SwordProjectileEntity>();
			roomChange = true;
		}
		if (pl->getPosition().y > Room::getHeightInPixels() - pl->getSprite()->getHeight()) {
			changeRoom(currentRow - 1, currentColumn);
			pl->setPositionY(0);
			roomChange = true;
		}
		if (pl->getPosition().y < 0) {
			changeRoom(currentRow + 1, currentColumn);
			pl->setPositionY(Room::getHeightInPixels() - pl->getSprite()->getHeight());
			roomChange = true;
		}
	}
}

void RoomManager::addRoom(Room* givenRoom, int givenRow, int givenColumn){
	if(roomArray[givenRow][givenColumn] == nullptr){
		roomArray[givenRow][givenColumn] = givenRoom;
	}
}

int RoomManager::getCurrentRow(){
	return currentRow;
}

int RoomManager::getCurrentColumn(){
	return currentColumn;
}

void RoomManager::changeRoom(int givenRow, int givenColumn){
	roomArray[givenRow][givenColumn]->removeTiles();
	currentRow = givenRow;
	currentColumn = givenColumn;
	roomArray[givenRow][givenColumn]->addTiles();
}
