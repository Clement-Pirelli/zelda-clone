#pragma once
#include <vector>

class Entity;
enum ENTITYTYPE;

class EntityManager{
public:
	EntityManager();
	~EntityManager();
	void update(float givenDeltaTime);
	void render();
	void addEntity(Entity* givenEntity);
	void removeEntity(Entity* givenEntity);
	template<typename T>
	std::vector<T*> getEntities(){
		std::vector<T*> returnVector;
		for (Entity* e : entities){
			T* castPtr = dynamic_cast<T*>(e);
			if (castPtr != nullptr){
				returnVector.push_back(castPtr);
			}
		}
		return returnVector;
	}
	std::vector<Entity*> getAllCollisionEntities();
	std::vector<Entity*> getAllEntities();
private:
	std::vector<Entity*> entities;
};