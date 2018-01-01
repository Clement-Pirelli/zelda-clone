#pragma once
#include "Entity.h"
#include <string>

enum ROOMTILETYPE;
class RenderManager;
class Sprite;
class Collider;

class Tile : public Entity{
public:
	Tile(std::string givenFilePath, int givenX, int givenY, ROOMTILETYPE givenTileType);
	virtual ~Tile();
	void update(float givenDeltaTime) override {};
	void render() override;
	Sprite* getSprite() override;
	virtual Collider* getCollider() override { return nullptr; };
	virtual void onCollision(Entity* otherEntity) override {};
	virtual ENTITYTYPE getType() override;
	SDL_Point getPosition() override;
protected:
	Sprite* mySprite = nullptr;
	RenderManager* myRenderManager = nullptr;
	SDL_Point position;
};