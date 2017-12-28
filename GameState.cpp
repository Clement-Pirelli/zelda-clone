#include "stdafx.h"
#include "GameState.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "RoomManager.h"
#include "PlayerAvatar.h"
#include "Service.h"
#include "Room.h"

GameState::GameState(){
	CollisionManager::addCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_OBSTACLE);
	CollisionManager::addCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_ENEMY);
	CollisionManager::addCollisionPair(ENTITYTYPE::ENTITY_PLAYER, ENTITYTYPE::ENTITY_HIDDEN_CAVE);
	myEntityManager = new EntityManager();
	Service<EntityManager>::setService(myEntityManager);
	PlayerAvatar* player = new PlayerAvatar(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_C, 100, 100);
	myEntityManager->addEntity(player);
	myRoomManager = new RoomManager();
	Service<RoomManager>::setService(myRoomManager);
	{
		//first room to show on screen

/*
		X O
		O O
*/

		{
			Room* tempRoom = new Room(ROOMENEMYTYPE::NO_ENEMY);
			std::array<std::array<ROOMTILETYPE, Room::heightInTiles>, Room::widthInTiles> tempArray;
			for (unsigned int i = 0; i < Room::widthInTiles; i++) {
				for (unsigned int j = 0; j < Room::heightInTiles; j++) {
					if (j != 3) {

						tempArray[i][j] = ROOMTILETYPE::GROUND;
					} else {
						tempArray[i][j] = ROOMTILETYPE::BUSH;
					}
				}
			}
			tempRoom->setTiles(Room::createTiles(tempArray));
			myRoomManager->addRoom(tempRoom, 0, 0);

			tempRoom->addTiles();
		}
		//room to the bottom of the first room
/*
		O O
		X O
*/

		{
			Room* tempRoom = new Room(ROOMENEMYTYPE::NO_ENEMY);
			std::array<std::array<ROOMTILETYPE, Room::heightInTiles>, Room::widthInTiles> tempArray;
			for (unsigned int i = 0; i < Room::widthInTiles; i++) {
				for (unsigned int j = 0; j < Room::heightInTiles; j++) {
					tempArray[i][j] = ROOMTILETYPE::BUSH;
				}
			}
			tempRoom->setTiles(Room::createTiles(tempArray));
			myRoomManager->addRoom(tempRoom, 0, 1);
		}

/*
		O X
		O O
*/

		{

		}

/*
		O O
		O X
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
		for (unsigned int j = 0; j < entities.size(); j++) {
			if (j == i) {
				continue;
			}
			if (CollisionManager::checkIfColliding(entities[i], entities[j])) {
				entities[i]->onCollision(entities[j]);
				entities[j]->onCollision(entities[i]);
			}
		}
	}
}

