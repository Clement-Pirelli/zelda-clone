#pragma once
#include <string>
#include <vector>
#include <map>

class Sprite;
class RenderManager;

class SpriteManager
{
public:
	SpriteManager();
	~SpriteManager();
	bool initialize(RenderManager* givenRenderManager);
	void shutdown();
	Sprite* createSprite(const std::string givenFile, int givenX, int givenY, int givenW, int givenH);
	void destroySprite(Sprite* givenSprite);
private:
	RenderManager* myRenderManager = nullptr;
	std::map<std::string, SDL_Texture*> textures;
	std::vector<Sprite*> sprites;
};

