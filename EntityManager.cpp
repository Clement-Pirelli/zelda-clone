#include "stdafx.h"
#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager(){
}

EntityManager::~EntityManager(){
	//if we remove an entity from the entites vector in the destructors, the "for" breaks
	std::vector<Entity*> ent = std::vector<Entity*>(entities);
	for (auto e : ent) {
		delete e;
		e = nullptr;
	}
}

void EntityManager::update(float givenDeltaTime){
	//if we remove an entity from the entites vector during the update, the "for" breaks
	std::vector<Entity*> ent = std::vector<Entity*>(entities);
	for (Entity* e : ent) {
		e->update(givenDeltaTime);
	}
}

void EntityManager::render(){
	for (Entity* e : entities) {
		e->render();
	}
}

void EntityManager::addEntity(Entity* givenEntity){
	if (givenEntity == nullptr) {
		return;
	}
	entities.push_back(givenEntity);
}

void EntityManager::removeEntity(Entity* givenEntity){
	if (givenEntity == nullptr) {
		return;
	}
	for (unsigned int i = 0; i < entities.size(); i++) {
		if (entities[i] == givenEntity) {
			//erase expects an iterator, begin() returns one
			//we therefore add i to the iterator to get to the right place
			entities.erase(entities.begin() + i);
			return;
		}
	}
}

std::vector<Entity*> EntityManager::getAllCollisionEntities(){
	std::vector<Entity*> returnVector;
	for (Entity* e : entities) {
		if (e->getCollider() != nullptr) {
			returnVector.push_back(e);
		}
	}
	return returnVector;
}

std::vector<Entity*> EntityManager::getAllEntities(){
	return entities;
}

