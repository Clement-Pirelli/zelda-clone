#include "stdafx.h"
#include "GameState.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "RoomManager.h"
#include "PlayerAvatar.h"
#include "Service.h"
#include "Room.h"

GameState::GameState(){
	myEntityManager = new EntityManager();
	Service<EntityManager>::setService(myEntityManager);
	PlayerAvatar* player = new PlayerAvatar(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_C, SDL_SCANCODE_V ,100, 50);
	myEntityManager->addEntity(player);
	myRoomManager = new RoomManager();
	Service<RoomManager>::setService(myRoomManager);
	{
		//first room to show on screen

/*
		X O O
		O O O
		O O O
*/

		{
			Room* tempRoom = new Room(ROOMENEMYTYPE::NO_ENEMY);
			std::array<std::array<ROOMTILETYPE, Room::heightInTiles>, Room::widthInTiles> tempArray;
			for (unsigned int i = 0; i < Room::widthInTiles; i++) {
				for (unsigned int j = 0; j < Room::heightInTiles; j++) {
					if (i == 0 || j == 0 || i == Room::widthInTiles - 1) {
						tempArray[i][j] = ROOMTILETYPE::ROCK_BOTTOM_MIDDLE;
					} else {
						if ( i < 2 && j == Room::heightInTiles - 1 || i > 4 && j == Room::heightInTiles - 1) {
							tempArray[i][j] = ROOMTILETYPE::ROCK_TOP_MIDDLE;
						} else {
							if (i == 1 && j == 1) {
								tempArray[i][j] = ROOMTILETYPE::ROCK_BOTTOM_RIGHT;
							} else {
								tempArray[i][j] = ROOMTILETYPE::GROUND;
							}
						}
					}
				}
			}
			tempRoom->setTiles(Room::createTiles(tempArray));
			myRoomManager->addRoom(tempRoom, 0, 0);

			tempRoom->addTiles();
		}

/*
		O X O
		O O O
		O O O
*/

		{
			Room* tempRoom = new Room(ROOMENEMYTYPE::NO_ENEMY);
			std::array<std::array<ROOMTILETYPE, Room::heightInTiles>, Room::widthInTiles> tempArray;
			for (unsigned int i = 0; i < Room::widthInTiles; i++) {
				for (unsigned int j = 0; j < Room::heightInTiles; j++) {
					tempArray[i][j] = ROOMTILETYPE::GROUND;
				}
			}
			tempRoom->setTiles(Room::createTiles(tempArray));
			tempRoom->setAsCave();
			myRoomManager->addRoom(tempRoom, 0, 1);
		}

/*
		O O O
		X O O
		O O O
*/

		{

		}

/*
		O O O
		O X O
		O O O
*/

		{

		}
		myRoomManager->addRoom(nullptr, 1, 0);
		myRoomManager->addRoom(nullptr, 1, 1);
	}
	
}


GameState::~GameState(){
	Service<RoomManager>::setService(nullptr);
	delete myRoomManager;
	myRoomManager = nullptr;
	delete myEntityManager;
	Service<EntityManager>::setService(nullptr);
	myEntityManager = nullptr;
}

bool GameState::update(float deltaTime){
	if (paused == false) {
		myEntityManager->update(deltaTime);
		checkCollision();
		myRoomManager->update();
	}
	myEntityManager->render();
	
	return true;
}

//TODO : do that stuff, look at the newest Tiberius around and figure out what should be put here
std::string GameState::getNextState(){
	return "";
}

void GameState::checkCollision(){
	std::vector<Entity*> entities = myEntityManager->getAllCollisionEntities();
	for (unsigned int i = 0; i < entities.size(); i++) {
		for (unsigned int j = i + 1; j < entities.size(); j++) {
			if (CollisionManager::checkIfColliding(entities[i], entities[j])) {
				entities[i]->onCollision(entities[j]);
				entities[j]->onCollision(entities[i]);
			}
		}
	}
}