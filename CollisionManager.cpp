#include "stdafx.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "RectangleCollider.h"
#include "Entity.h"

CollisionManager::CollisionManager(){
}


CollisionManager::~CollisionManager(){
}

bool CollisionManager::checkIfColliding(Entity* givenLeftEntity, Entity* givenRightEntity){
	if (givenLeftEntity != nullptr && givenRightEntity != nullptr) {
		if (givenLeftEntity->getCollider() == nullptr || givenRightEntity->getCollider() == nullptr) {
			return false;
		}
		return checkIfColliding(givenLeftEntity->getCollider(), givenRightEntity->getCollider());
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
