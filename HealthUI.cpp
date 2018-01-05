#include "stdafx.h"
#include "HealthUI.h"
#include "Service.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "RenderManager.h"
#include "PlayerAvatar.h"
#include "RenderManager.h"

HealthUI::HealthUI(PlayerAvatar* givenPlayer){
	myRenderManager = Service<RenderManager>::getService();
	myPlayer = givenPlayer;
	heartSprite = Service<SpriteManager>::getService()->createSprite("../Assets/hearts_UI.png", 0, 0, HEART_SPRITE_DIMENSION.x, HEART_SPRITE_DIMENSION.y);
	halfHeartSprite = Service<SpriteManager>::getService()->createSprite("../Assets/hearts_UI.png", HEART_SPRITE_DIMENSION.x, 0, HEART_SPRITE_DIMENSION.x, HEART_SPRITE_DIMENSION.y);
	emptyHeartSprite = Service<SpriteManager>::getService()->createSprite("../Assets/hearts_UI.png", HEART_SPRITE_DIMENSION.x * 2, 0, HEART_SPRITE_DIMENSION.x, HEART_SPRITE_DIMENSION.y);
	lifeTextSprite = Service<SpriteManager>::getService()->createSprite("../Assets/life_text_UI.png", 0, 0, 92, 14);
}

HealthUI::~HealthUI(){
	emptyHeartSprite = nullptr;
	halfHeartSprite = nullptr;
	heartSprite = nullptr;
	myPlayer = nullptr;
	myRenderManager = nullptr;
}

void HealthUI::render(){
	int tempHealth = myPlayer->getHealth();
	for (unsigned int i = 0; i < static_cast<int>(myPlayer->getMaxHealth() / 2); i++){
		if (tempHealth > 1){
			myRenderManager->draw(heartSprite, HEART_BAR_POSITION.x + i * (HEART_SPRITE_DIMENSION.x + 2), HEART_BAR_POSITION.y);
			tempHealth -= 2;
		} else {
			if (tempHealth == 1){
				myRenderManager->draw(halfHeartSprite, HEART_BAR_POSITION.x + i * (HEART_SPRITE_DIMENSION.x + 2), HEART_BAR_POSITION.y);
				tempHealth -= 1;
			} else {
				myRenderManager->draw(emptyHeartSprite, HEART_BAR_POSITION.x + i * (HEART_SPRITE_DIMENSION.x + 2), HEART_BAR_POSITION.y);
			}
		}
	}
	myRenderManager->draw(lifeTextSprite, HEART_BAR_POSITION.x, HEART_BAR_POSITION.y - HEART_SPRITE_DIMENSION.y - lifeTextSprite->getHeight());
}
