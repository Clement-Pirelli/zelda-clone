#pragma once
#include <array>
#include "EngineConfig.h"

enum ROOMENEMYTYPE {
	PROJECTILE_ENEMY,
	JUMPING_ENEMY,
	MIXED,
	NO_ENEMY
};

enum ROOMTILETYPE {
	ROCK_TOP_LEFT = 0,
	ROCK_TOP_MIDDLE = 1,
	ROCK_TOP_RIGHT = 2,
	ROCK_BOTTOM_LEFT = 5,
	ROCK_BOTTOM_MIDDLE = 6,
	ROCK_BOTTOM_RIGHT = 7,
	GROUND = 3,
	CAVE = 4,
	BUSH = 8,
	HIDDEN_CAVE = 9
};

class Tile;

class Room{
public:
	static const int tileWidth = 32;
	static const int tileHeight = 32;
	static const int widthInTiles = 20;
	static const int heightInTiles = 15;
	SDL_Point getSpecialDestination();
	void setSpecialDestination(int givenRow, int givenColumn);
	static int getWidthInPixels();
	static int getHeightInPixels();
	Room(ROOMENEMYTYPE givenEnemyType);
	~Room();
	static std::array<std::array<Tile*, Room::heightInTiles>, Room::widthInTiles> createTiles(std::array<std::array<ROOMTILETYPE,Room::heightInTiles>, Room::widthInTiles> givenArray);
	void setTiles(std::array<std::array<Tile*, Room::heightInTiles>, Room::widthInTiles> givenTileArray);
	void spawn();
	void addTiles();
	void removeTiles();
private:
	SDL_Point specialDestination{ -1, -1};
	std::array<std::array<Tile*, Room::heightInTiles>, Room::widthInTiles> tiles;
	ROOMENEMYTYPE myEnemyType;
	static const int enemySpawnAmount = 4;
};