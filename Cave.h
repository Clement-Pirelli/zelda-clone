#pragma once
#include "Obstacle.h"

class Sprite;

class Cave : public Obstacle{
public:
	Cave(std::string givenFilePath, int givenX, int givenY, ROOMTILETYPE givenTileType);
	~Cave();
	Collider* getCollider() override;
	void onCollision(Entity* otherEntity) override;
	ENTITYTYPE getType() override;
private:
	bool opened = false;
	Sprite* openedSprite = nullptr;
};

