#include "stdafx.h"
#include "Room.h"
#include "Sprite.h"
#include "Service.h"
#include "Tile.h"
#include "Obstacle.h"
#include "RenderManager.h"
#include "EntityManager.h"

SDL_Point Room::getSpecialDestination(){
	return specialDestination;
}

void Room::setSpecialDestination(int givenRow, int givenColumn){
	specialDestination.x = givenRow;
	specialDestination.y = givenColumn;
}

int Room::getWidthInPixels(){
	return widthInTiles * tileWidth;
}

int Room::getHeightInPixels(){
	return heightInTiles * tileHeight;
}

Room::Room(ROOMENEMYTYPE givenEnemyType){
	for (unsigned int i = 0; i < tiles.size() - 1; i++) {
		for (unsigned int j = 0; j < tiles[i].size() - 1; j++) {
			tiles[i][j] = nullptr;
		}
	}
	myEnemyType = givenEnemyType;
}

Room::~Room(){
	removeTiles();
	for (unsigned int i = 0; i < tiles.size() - 1; i++) {
		for (unsigned int j = 0; j < tiles[i].size() - 1; j++) {
			if (tiles[i][j] != nullptr) {
				delete tiles[i][j];
				tiles[i][j] = nullptr;
			}
		}
	}
}

//TODO: factory which creates tiles according to an array of enums
std::array<std::array<Tile*, Room::heightInTiles>, Room::widthInTiles> Room::createTiles(std::array<std::array<ROOMTILETYPE, Room::heightInTiles>, Room::widthInTiles> givenArray){
	std::array<std::array<Tile*, Room::heightInTiles>, Room::widthInTiles> returnArray;
	Tile* tile = nullptr;
	for (unsigned int i = 0; i < givenArray.size(); i++) {
		for (unsigned int j = 0; j < givenArray[i].size() ; j++) {
			switch (givenArray[i][j]) {
			case ROOMTILETYPE::ROCK_BOTTOM_LEFT:
			case ROOMTILETYPE::ROCK_BOTTOM_MIDDLE:
			case ROOMTILETYPE::ROCK_BOTTOM_RIGHT:
			case ROOMTILETYPE::ROCK_TOP_LEFT:
			case ROOMTILETYPE::ROCK_TOP_MIDDLE:
			case ROOMTILETYPE::ROCK_TOP_RIGHT:
			case ROOMTILETYPE::BUSH:

				tile = new Obstacle("../Assets/tiles.png", Room::tileWidth * i, Room::tileHeight * j, givenArray[i][j]);
				returnArray[i][j] = tile;
				break;
			case ROOMTILETYPE::CAVE:
				//TODO : IMPLEMENT CAVES
				break;
			case ROOMTILETYPE::HIDDEN_CAVE:
				//TODO : IMPLEMENT CAVES
				break;
			case ROOMTILETYPE::GROUND:
				tile = new Tile("../Assets/tiles.png", Room::tileWidth * i, Room::tileHeight * j, givenArray[i][j]);
				
				break;
			default:
				tile = new Tile("../Assets/tiles.png", Room::tileWidth * i, Room::tileHeight * j, ROOMTILETYPE::CAVE);
				break;
			}
			returnArray[i][j] = tile;
		}
	}
	return returnArray;
}

void Room::setTiles(std::array<std::array<Tile*, Room::heightInTiles>, Room::widthInTiles> givenTileArray){
	for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[i].size(); j++) {
			tiles[i][j] = givenTileArray[i][j];
		}
	}
}

//TODO : factory which spawns enemies according to their enemy type at the start of the game
void Room::spawn(){
	switch (myEnemyType) {
	case ROOMENEMYTYPE::JUMPING_ENEMY:
		for (unsigned int i = 0; i < Room::enemySpawnAmount; i++) {
			//spawn jumping enemies randomly in the middle of the room, being careful as to not collide with anything
		}
		break;
	case ROOMENEMYTYPE::PROJECTILE_ENEMY:
		for (unsigned int i = 0; i < Room::enemySpawnAmount; i++) {
			//spawn projectile enemies randomly in the middle of the room, being careful as to not collide with anything
		}
		break;
	case ROOMENEMYTYPE::MIXED:
		for (unsigned int i = 0; i < Room::enemySpawnAmount; i++) {
			//spawn half of both enemies randomly in the middle of the room, being careful as to not collide with anything
		}
		break;
	}
}

void Room::addTiles(){
	for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[i].size(); j++) {
			if (tiles[i][j] != nullptr) {
				Service<EntityManager>::getService()->addEntity(tiles[i][j]);
			}
		}
	}
}

void Room::removeTiles(){
	for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[i].size(); j++) {
			if (tiles[i][j] != nullptr) {
				Service<EntityManager>::getService()->removeEntity(tiles[i][j]);
			}
		}
	}
}
