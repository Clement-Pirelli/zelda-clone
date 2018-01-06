#pragma once
#include "RenderInfo.h"

class PlayerAvatar;
class RenderManager;
class Sprite;
class NumberFont;

class PlayerVariablesUI{
public:
	PlayerVariablesUI(PlayerAvatar* givenPlayer);
	~PlayerVariablesUI();
	void render();
private:
	RenderManager* myRenderManager = nullptr;
	PlayerAvatar* myPlayer = nullptr;
	NumberFont* myFont = nullptr;
	Sprite* rupeeSprite = nullptr;
	Sprite* bombSprite = nullptr;
	Sprite* keySprite = nullptr;
	const SDL_Point SPRITE_DIMENSIONS{ 16,16 };
	const SDL_Point RUPEE_SPRITE_POSITION{ 100, 70 - RenderInfo::UI_HEIGHT };
	const SDL_Point KEY_SPRITE_POSITION{ RUPEE_SPRITE_POSITION.x, RUPEE_SPRITE_POSITION.y + (SPRITE_DIMENSIONS.y * 2)};
	const SDL_Point BOMB_SPRITE_POSITION{ RUPEE_SPRITE_POSITION.x, RUPEE_SPRITE_POSITION.y + (SPRITE_DIMENSIONS.y * 3)};
};

