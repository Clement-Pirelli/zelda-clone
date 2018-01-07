#include "stdafx.h"
#include "Room.h"
#include "Sprite.h"
#include "Service.h"
#include "Tile.h"
#include "Obstacle.h"
#include "Cave.h"
#include "RenderManager.h"
#include "EntityManager.h"
#include "Utilities.h"
#include "ShootingEnemy.h"
#include "JumpingEnemy.h"

bool Room::getIfCave(){
	return isCave;
}

void Room::setAsCave(){
	isCave = true;
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
	checkIfCleared();
	removeTiles();
	for (unsigned int i = 0; i < tiles.size(); i++) {
		for (unsigned int j = 0; j < tiles[i].size(); j++) {
			if (tiles[i][j] != nullptr) {
				delete tiles[i][j];
				tiles[i][j] = nullptr;
			}
		}
	}
}

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
			case ROOMTILETYPE::HIDDEN_CAVE:
				tile = new Cave("../Assets/tiles.png", Room::tileWidth * i, Room::tileHeight * j, givenArray[i][j]);
				break;
			case ROOMTILETYPE::GROUND:
			case ROOMTILETYPE::NOTHING:
				tile = new Tile("../Assets/tiles.png", Room::tileWidth * i, Room::tileHeight * j, givenArray[i][j]);
				break;
			case ROOMTILETYPE::CAVE:
				Cave* cave = new Cave("../Assets/tiles.png", Room::tileWidth * i, Room::tileHeight * j, givenArray[i][j]);
				cave->setOpened();
				tile = cave;
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
	if (isCleared == false && myEnemyType != ROOMENEMYTYPE::NO_ENEMY) {
		std::vector<Enemy*> enemies;
		for (unsigned int i = 0; i < Room::enemySpawnAmount; i++) {
			//spawn enemies randomly in the middle of the room, being careful as to not collide with anything
			bool spawned = false;
			while (spawned == false) {
				int rRow = Utilities::random(Room::widthInTiles - 13, Room::widthInTiles - 7);
				int rColumn = Utilities::random(Room::heightInTiles - 10, Room::heightInTiles - 5);
				if (tiles[rRow][rColumn]->getType() != ENTITYTYPE::ENTITY_OBSTACLE) {
					int okCount = 0;
					for (auto e : enemies) {
						if (e->getPosition().x == rRow * Room::widthInTiles && e->getPosition().y == rColumn * Room::heightInTiles) {
							break;
						} else {
							okCount++;
						}
					}
					if (okCount >= enemies.size()) {
						if (myEnemyType == ROOMENEMYTYPE::JUMPING_ENEMY){
							new JumpingEnemy(rRow * Room::widthInTiles, rColumn * Room::heightInTiles);
						} else {
							if (myEnemyType == ROOMENEMYTYPE::SHOOTING_ENEMY){
								new ShootingEnemy(rRow * Room::widthInTiles, rColumn * Room::heightInTiles);
							} else {
								if (myEnemyType == ROOMENEMYTYPE::MIXED){
									if (i > Room::enemySpawnAmount / 2){
										new JumpingEnemy(rRow * Room::widthInTiles, rColumn * Room::heightInTiles);
									} else {
										new ShootingEnemy(rRow * Room::widthInTiles, rColumn * Room::heightInTiles);
									}
								}
							}
						}
						spawned = true;
					}
				}
			}
		}
	}
}

void Room::checkIfCleared(){
	if (enemyCount <= 0 && isCleared == false) {
		isCleared = true;
	} else {
		int enemyCount = enemySpawnAmount;
	}
}

void Room::decrementEnemyCount(){
	enemyCount--;
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
			Service<EntityManager>::getService()->removeEntity(tiles[i][j]);
		}
	}
}
