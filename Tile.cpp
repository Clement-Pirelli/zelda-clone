#include "stdafx.h"
#include "Tile.h"
#include "Service.h"
#include "RenderManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "Room.h"
#include "LayerInfo.h"

Tile::Tile(std::string givenFilePath, int givenX, int givenY, ROOMTILETYPE givenTileType){
	position.x = givenX;
	position.y = givenY;
	myRenderManager = Service<RenderManager>::getService();
	mySprite = Service<SpriteManager>::getService()->createSprite(givenFilePath, givenTileType * Room::tileWidth, 0, Room::tileWidth, Room::tileHeight);
}


Tile::~Tile(){
	myRenderManager = nullptr;
	Service<SpriteManager>::getService()->destroySprite(mySprite);
	mySprite = nullptr;
}

void Tile::render(){
	myRenderManager->draw(mySprite, position.x, position.y, LayerInfo::tileLayer);
}

Sprite* Tile::getSprite(){
	return mySprite;
}

ENTITYTYPE Tile::getType(){
	return ENTITYTYPE::ENTITY_TILE;
}

SDL_Point Tile::getPosition(){
	return position;
}
