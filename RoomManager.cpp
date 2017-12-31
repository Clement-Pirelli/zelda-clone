#include "stdafx.h"
#include "RoomManager.h"
#include "Room.h"
#include "Service.h"
#include "EntityManager.h"
#include "PlayerAvatar.h"
#include "Sprite.h"
#include "Cave.h"
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
	//we assume there is only one player
	PlayerAvatar* pl = Service<EntityManager>::getService()->getEntities<PlayerAvatar>()[0];
	//This assumes that the player cannot go out of bounds, aka that the level design is sound.
	if (roomArray[currentRow][currentColumn]->getIfCave() == false) {
		if (pl->getPosition().x > Room::getWidthInPixels() - pl->getSprite()->getWidth()) {
			changeRoom(currentRow, currentColumn + 1);
			pl->setPositionX(0);
			roomChange = true;
		}
		else {
			if (pl->getPosition().x < 0) {
				changeRoom(currentRow, currentColumn - 1);
				pl->setPositionX(Room::getWidthInPixels() - pl->getSprite()->getWidth());
				roomChange = true;
			}
			else {
				if (pl->getPosition().y > Room::getHeightInPixels() - pl->getSprite()->getHeight()) {
					changeRoom(currentRow - 1, currentColumn);
					pl->setPositionY(0);
					roomChange = true;
				}
				else {
					if (pl->getPosition().y < 0) {
						changeRoom(currentRow + 1, currentColumn);
						pl->setPositionY(Room::getHeightInPixels() - pl->getSprite()->getHeight());
						roomChange = true;
					}
				}
			}
		}
	} else {
		if (pl->getPosition().x > Room::getWidthInPixels() - pl->getSprite()->getWidth() ||
			pl->getPosition().x < 0 ||
			pl->getPosition().y > Room::getHeightInPixels() - pl->getSprite()->getHeight() ||
			pl->getPosition().y < 0
			) {
			changeRoomFromCave();
			//we assume there is only one room
			Cave* cave = Service<EntityManager>::getService()->getEntities<Cave>()[0];
			pl->setPositionX(cave->getPosition().x);
			pl->setPositionY(cave->getPosition().y + cave->getSprite()->getHeight() + 3);
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
	roomArray[currentRow][currentColumn]->removeTiles();
	roomArray[givenRow][givenColumn]->checkIfCleared();
	currentRow = givenRow;
	currentColumn = givenColumn;
	roomArray[givenRow][givenColumn]->addTiles();
	roomArray[givenRow][givenColumn]->spawn();
}

void RoomManager::changeRoomFromCave(){
	changeRoom(currentRow, currentColumn - 1);
}
