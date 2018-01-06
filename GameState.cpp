#include "stdafx.h"
#include "GameState.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "CollisionManager.h"
#include "RenderManager.h"
#include "RoomManager.h"
#include "PlayerAvatar.h"
#include "Service.h"
#include "Room.h"
#include "Inventory.h"
#include "EngineConfig.h"
#include "RenderInfo.h"
#include "UI.h"
#include "NumberFont.h"

GameState::GameState(){
	myFont = new NumberFont("../Assets/numbers_font.png", 14, 14);
	Service<NumberFont>::setService(myFont);
	myEntityManager = new EntityManager();
	Service<EntityManager>::setService(myEntityManager);
	myInputManager = Service<InputManager>::getService();
	myPlayer = new PlayerAvatar(SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_C, SDL_SCANCODE_X ,100, 50);
	myEntityManager->addEntity(myPlayer);
	myRoomManager = new RoomManager();
	Service<RoomManager>::setService(myRoomManager);
	myUI = new UI(myPlayer);
	createRooms();
}


GameState::~GameState(){
	delete myUI;
	myUI = nullptr;
	Service<RoomManager>::setService(nullptr);
	delete myRoomManager;
	myRoomManager = nullptr;
	myInputManager = nullptr;
	myEntityManager->removeEntity(myPlayer);
	delete myPlayer;
	myPlayer = nullptr;
	delete myEntityManager;
	myEntityManager = nullptr;
	Service<EntityManager>::setService(nullptr);
	Service<NumberFont>::setService(nullptr);
	delete myFont;
	myFont = nullptr;
}

void GameState::enter(){
	//play the music
}

bool GameState::update(float deltaTime){
	if (paused == false) {
		myEntityManager->update(deltaTime);
		checkCollision();
		myRoomManager->update();
		if (myPlayer->getHealth() <= 0){
			return false;
		}
	} else {
		myPlayer->getInventory()->draw();
		myPlayer->getInventory()->checkInput();
	}
	myEntityManager->render();
	myUI->render();
	checkInput();
	return true;
}

void GameState::exit(){
	//stop playing the music
}

//TODO : put the game over state here
std::string GameState::getNextState(){
	return "gameOverState";
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

void GameState::checkInput(){
	if (myInputManager->isKeyPressed(inventoryKey)) {
		if (paused == true){
			paused = false;
			Service<RenderManager>::getService()->addToCameraPosition(0, -(EngineConfig::WINDOW_HEIGHT - RenderInfo::UI_HEIGHT));
		} else {
			paused = true;
			Service<RenderManager>::getService()->addToCameraPosition(0, EngineConfig::WINDOW_HEIGHT - RenderInfo::UI_HEIGHT);
		}
	}
}

//TODO : flesh this out in the final stages of production
void GameState::createRooms(){
	//first room to show on screen

	/*
	X O O
	O O O
	O O O
	*/

	{
		Room* tempRoom = new Room(ROOMENEMYTYPE::JUMPING_ENEMY);
		std::array<std::array<ROOMTILETYPE, Room::heightInTiles>, Room::widthInTiles> tempArray;
		for (unsigned int i = 0; i < Room::widthInTiles; i++) {
			for (unsigned int j = 0; j < Room::heightInTiles; j++) {
				if (i == 0 || j == 0 || i == Room::widthInTiles - 1) {
					tempArray[i][j] = ROOMTILETYPE::ROCK_BOTTOM_MIDDLE;
				} else {
					if (i < 2 && j == Room::heightInTiles - 1 || i > 4 && j == Room::heightInTiles - 1) {
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

		myRoomManager->changeRoom(0, 0);
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