#pragma once
#include "RenderInfo.h"

class PlayerAvatar;
class Sprite;
class RenderManager;

class HealthUI{
public:
	HealthUI(PlayerAvatar* givenPlayer);
	~HealthUI();
	void render();
private:
	RenderManager* myRenderManager = nullptr;
	PlayerAvatar* myPlayer = nullptr;
	Sprite* heartSprite = nullptr;
	Sprite* halfHeartSprite = nullptr;
	Sprite* emptyHeartSprite = nullptr;
	Sprite* lifeTextSprite = nullptr;
	const SDL_Point HEART_SPRITE_DIMENSION{ 14, 16 };
	const SDL_Point HEART_BAR_POSITION{ 450, 100 - RenderInfo::UI_HEIGHT };
};