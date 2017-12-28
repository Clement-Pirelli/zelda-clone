#pragma once
#include "Tile.h"

class RectangleCollider;

class Obstacle : public Tile{
public:
	Obstacle(std::string givenFilePath, int givenX, int givenY, ROOMTILETYPE givenTileType);
	virtual ~Obstacle();
	virtual Collider* getCollider() override;
	virtual ENTITYTYPE getType() override;
protected:
	RectangleCollider* myCollider = nullptr;
};

