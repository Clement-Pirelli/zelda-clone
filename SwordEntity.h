#pragma once
#include "Entity.h"
#include <string>

enum SWORDDIRECTION {
	S_UP,
	S_DOWN,
	S_LEFT,
	S_RIGHT,
};

class Sprite;
class RectangleCollider;
class RenderManager;
class PlayerAvatar;

class SwordEntity : public Entity{
public:
	SwordEntity();
	virtual ~SwordEntity();
	virtual int getDamage() = 0;
	void reposition(PlayerAvatar* givenPlayer);
	void setCollisionActive(bool givenActive);
	SWORDDIRECTION getDirection();
	SDL_Point getPosition() override;
	Collider* getCollider() override;
	ENTITYTYPE getType() override;
	Sprite* getSprite() override;
protected:
	bool collisionActive = true;
	Sprite* mySprite = nullptr;
	RectangleCollider* myCollider = nullptr;
	RenderManager* myRenderManager = nullptr;
	SWORDDIRECTION direction;
	SDL_Point position;
	std::string verticalSpriteFilePath;
	std::string horizontalSpriteFilePath;
};

