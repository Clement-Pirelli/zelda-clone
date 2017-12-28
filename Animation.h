#pragma once
#include <vector>

class Sprite;

class Animation{
public:
	Animation(std::vector<Sprite*> givenSprites, float givenTimer = 0.3f);
	~Animation();
	Sprite* getCurrentSprite();
	void tick(float givenDeltaTime);
	void setIndex(int givenIndex);
	void setTimer(float givenTimer);
	float getTimer() const;
	void setIfActive(bool isActive);
	void setFlip(SDL_RendererFlip givenFlip);
private:
	bool active = true;
	float timer = 0.0f;
	float timePassed = 0.0f;
	int spriteIndex = 0;
	std::vector<Sprite*> sprites;
	Sprite* currentSprite = nullptr;
};

