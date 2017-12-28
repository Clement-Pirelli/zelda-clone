#pragma once
#include <vector>
#include "Entity.h"

class Collider;

class CollisionManager{
public:
	~CollisionManager();
	static bool checkIfColliding(Entity* givenLeftEntity, Entity* givenRightEntity);
	static bool checkIfColliding(Collider* givenLeftEntity, Collider* givenRightEntity);
	static bool checkIfColliding(SDL_Rect givenLeftRect, SDL_Rect givenRightRect);
private:
	CollisionManager();
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
};