#pragma once
#include "Obstacle.h"

class Sprite;

class Cave : public Obstacle{
public:
	Cave(std::string givenFilePath, int givenX, int givenY, ROOMTILETYPE givenTileType, bool isOpened = false);
	~Cave();
	void setOpened();
	Collider* getCollider() override;
	void render() override;
	void onCollision(Entity* otherEntity) override;
	ENTITYTYPE getType() override;
private:
	bool opened = false;
};

