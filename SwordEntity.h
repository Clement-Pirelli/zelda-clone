#pragma once
#include "Entity.h"

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
	void reposition(PlayerAvatar* givenPlayer);
	SWORDDIRECTION getDirection();
	SDL_Point getPosition();
	Collider* getCollider() override;
	ENTITYTYPE getType() override;
	Sprite* getSprite() override;
protected:
	Sprite* mySprite = nullptr;
	Collider* myCollider = nullptr;
	RenderManager* myRenderManager = nullptr;
	SWORDDIRECTION direction;
	SDL_Point position;
	std::string verticalSpriteFilePath;
	std::string horizontalSpriteFilePath;
};

