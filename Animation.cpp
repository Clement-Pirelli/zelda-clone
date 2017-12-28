#include "stdafx.h"
#include "Animation.h"
#include "Service.h"
#include "SpriteManager.h"
#include "Sprite.h"

Animation::Animation(std::vector<Sprite*> givenSprites, float givenTimer){
	timer = givenTimer;
	sprites = givenSprites;
	currentSprite = sprites[spriteIndex];
}

Animation::~Animation(){
	for (unsigned int i = 0; i < sprites.size() - 1; i++) {
		Service<SpriteManager>().getService()->destroySprite(sprites[i]);
	}
	sprites.clear();
	currentSprite = nullptr;
	spriteIndex = 0;
}

Sprite* Animation::getCurrentSprite(){
	return currentSprite;
}

void Animation::tick(float givenDeltaTime){
	if (active == true) {
		timePassed += givenDeltaTime;
		if ((timePassed) >= timer) {
			spriteIndex++;
			if (spriteIndex > sprites.size() - 1) {
				spriteIndex = 0;
			}
			currentSprite = sprites[spriteIndex];
			timePassed = 0;
		}
	}
}

void Animation::setIndex(int givenIndex){
	spriteIndex = givenIndex;
}

void Animation::setTimer(float givenTimer){
	timer = givenTimer;
}

float Animation::getTimer() const{
	return timer;
}

void Animation::setIfActive(bool isActive){
	active = isActive;
}

void Animation::setFlip(SDL_RendererFlip givenFlip){
	for (auto s : sprites) {
		s->setFlip(givenFlip);
	}
}
