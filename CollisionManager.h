#pragma once
#include <vector>
#include "Entity.h"

class Collider;

class CollisionManager{
public:
	~CollisionManager();
	static void addCollisionPair(ENTITYTYPE firstGivenType, ENTITYTYPE secondGivenType);
	static void removeCollisionPair(ENTITYTYPE firstGivenType, ENTITYTYPE secondGivenType);
	static bool checkIfColliding(Entity* givenLeftEntity, Entity* givenRightEntity);
	static bool checkIfColliding(Collider* givenLeftEntity, Collider* givenRightEntity);
	static bool checkIfColliding(SDL_Rect givenLeftRect, SDL_Rect givenRightRect);
private:
	static std::vector<std::pair<ENTITYTYPE, ENTITYTYPE>> collisionPairs;
	CollisionManager();
	CollisionManager(const CollisionManager& other) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;
};