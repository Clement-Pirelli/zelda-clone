#include "stdafx.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "RectangleCollider.h"
#include "Entity.h"

std::vector<std::pair<ENTITYTYPE, ENTITYTYPE>> CollisionManager::collisionPairs;

CollisionManager::CollisionManager(){
}


CollisionManager::~CollisionManager(){
}

void CollisionManager::addCollisionPair(ENTITYTYPE firstGivenType, ENTITYTYPE secondGivenType){
	for (unsigned int i = 0; i < collisionPairs.size(); i++) {
		if (
		(collisionPairs[i].first == firstGivenType && collisionPairs[i].second == secondGivenType)
		|| (collisionPairs[i].first == secondGivenType && collisionPairs[i].second == firstGivenType)
		) {
			return;
		}
	}
	collisionPairs.push_back(std::make_pair(firstGivenType, secondGivenType));
}

void CollisionManager::removeCollisionPair(ENTITYTYPE firstGivenType, ENTITYTYPE secondGivenType){
	for (unsigned int i = 0; i < collisionPairs.size(); i++) {
		if (
			(collisionPairs[i].first == firstGivenType && collisionPairs[i].second == secondGivenType)
			|| (collisionPairs[i].first == secondGivenType && collisionPairs[i].second == firstGivenType)
			) {
			collisionPairs.erase(collisionPairs.begin() + i);
		}
	}
}

bool CollisionManager::checkIfColliding(Entity* givenLeftEntity, Entity* givenRightEntity){
	if (givenLeftEntity->getCollider() == nullptr || givenRightEntity->getCollider() == nullptr) {
		return false;
	}
	for (unsigned int i = 0; i < collisionPairs.size(); i++) {
		if (
			(collisionPairs[i].first == givenRightEntity->getType() && collisionPairs[i].second == givenLeftEntity->getType())
			|| (collisionPairs[i].first == givenRightEntity->getType() && collisionPairs[i].second == givenLeftEntity->getType())
			) {
			return checkIfColliding(givenLeftEntity->getCollider(), givenRightEntity->getCollider());
		}
	}
	return false;
}

bool CollisionManager::checkIfColliding(Collider* givenLeftCollider, Collider* givenRightCollider){
	if (givenLeftCollider->getType() == COLLIDERTYPE::RECTANGLE && givenRightCollider->getType() == COLLIDERTYPE::RECTANGLE) {
		RectangleCollider* leftRect = dynamic_cast<RectangleCollider*>(givenLeftCollider);
		RectangleCollider* rightRect = dynamic_cast<RectangleCollider*>(givenRightCollider);
		return checkIfColliding(leftRect->getRectangle(), rightRect->getRectangle());
	}
	return false;
}

bool CollisionManager::checkIfColliding(SDL_Rect leftRect, SDL_Rect rightRect){
	int aLeft, aRight, aTop, aBottom;
	int bLeft, bRight, bTop, bBottom;
	aLeft = leftRect.x;
	aRight = leftRect.x + leftRect.w;
	aTop = leftRect.y;
	aBottom = leftRect.y + leftRect.h;

	bLeft = rightRect.x;
	bRight = rightRect.x + rightRect.w;
	bTop = rightRect.y;
	bBottom = rightRect.y + rightRect.h;

	if (aLeft > bRight || aRight < bLeft || aTop > bBottom || aBottom < bTop) {
		return false;
	}
	return true;
}
