#include "stdafx.h"
#include "PlayerVariablesUI.h"
#include "Service.h"
#include "RenderManager.h"
#include "NumberFont.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "PlayerAvatar.h"
#include "Inventory.h"
#include "BombItem.h"

PlayerVariablesUI::PlayerVariablesUI(PlayerAvatar* givenPlayer){
	myPlayer = givenPlayer;
	myRenderManager = Service<RenderManager>::getService();
	myFont = Service<NumberFont>::getService();
	keySprite = Service<SpriteManager>::getService()->createSprite("../Assets/key_variable_UI.png", 0, 0, SPRITE_DIMENSIONS.x, SPRITE_DIMENSIONS.y);
	bombSprite = Service<SpriteManager>::getService()->createSprite("../Assets/bomb_variable_UI.png", 0, 0, SPRITE_DIMENSIONS.x, SPRITE_DIMENSIONS.y);
	rupeeSprite = Service<SpriteManager>::getService()->createSprite("../Assets/rupee_variable_UI.png", 0, 0, SPRITE_DIMENSIONS.x, SPRITE_DIMENSIONS.y);
}

PlayerVariablesUI::~PlayerVariablesUI(){
	Service<SpriteManager>::getService()->destroySprite(rupeeSprite);
	rupeeSprite = nullptr;
	Service<SpriteManager>::getService()->destroySprite(bombSprite);
	bombSprite = nullptr;
	Service<SpriteManager>::getService()->destroySprite(keySprite);
	keySprite = nullptr;
	myRenderManager = nullptr;
	myPlayer = nullptr;
}

void PlayerVariablesUI::render(){
	myRenderManager->draw(rupeeSprite, RUPEE_SPRITE_POSITION.x, RUPEE_SPRITE_POSITION.y);
	myRenderManager->draw(keySprite, KEY_SPRITE_POSITION.x, KEY_SPRITE_POSITION.y);
	myRenderManager->draw(bombSprite, BOMB_SPRITE_POSITION.x, BOMB_SPRITE_POSITION.y);
	myFont->render(SDL_Point{ RUPEE_SPRITE_POSITION.x + SPRITE_DIMENSIONS.x, RUPEE_SPRITE_POSITION.y}, myPlayer->getRupeeCount());
	myFont->render(SDL_Point{ KEY_SPRITE_POSITION.x + SPRITE_DIMENSIONS.x, KEY_SPRITE_POSITION.y}, myPlayer->getKeyCount());
	if (myPlayer->getInventory()->getItem<BombItem>() != nullptr){
		myFont->render(SDL_Point{ BOMB_SPRITE_POSITION.x + SPRITE_DIMENSIONS.x, BOMB_SPRITE_POSITION.y }, myPlayer->getInventory()->getItem<BombItem>()->getBombCount());
	} else {
		myFont->render(SDL_Point{ BOMB_SPRITE_POSITION.x + SPRITE_DIMENSIONS.x, BOMB_SPRITE_POSITION.y }, 0);
	}
}