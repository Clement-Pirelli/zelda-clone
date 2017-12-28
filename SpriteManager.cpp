#include "stdafx.h"
#include "SpriteManager.h"
#include "RenderManager.h"
#include "Sprite.h"

SpriteManager::SpriteManager(){
}


SpriteManager::~SpriteManager(){
}

bool SpriteManager::initialize(RenderManager * givenRenderManager){
	if (givenRenderManager == nullptr) {
		return false;
	}
	myRenderManager = givenRenderManager;
	return true;
}

void SpriteManager::shutdown(){
	//iterate through the "sprites" vector and delete every sprite
	for (Sprite* sprite : sprites) {
		delete sprite;
		//reset the pointer, in case anyone is using it
		sprite = nullptr;
	}
	//iterate through the "textures" map and destroy every texture
	//auto is equal to std::pair<std::string, SDL_Texture*>
	for (auto texturePair : textures) {
		SDL_DestroyTexture(texturePair.second);
	}
	//remove the pointers to now deleted textures
	textures.clear();
}

Sprite* SpriteManager::createSprite(const std::string givenFile, int givenX, int givenY, int givenW, int givenH){
	auto iterator = textures.find(givenFile);
	if (iterator == textures.end()) {
		SDL_Surface* surface = IMG_Load(givenFile.c_str());
		SDL_Texture* texture = SDL_CreateTextureFromSurface(myRenderManager->getRenderer(), surface);
		SDL_FreeSurface(surface);
		textures.insert(std::pair<std::string, SDL_Texture*>(givenFile, texture));
		iterator = textures.find(givenFile);
	}
	Sprite* sprite = new Sprite(iterator->second,givenX, givenY, givenW, givenH);
	sprites.push_back(sprite);
	return sprite;
}

void SpriteManager::destroySprite(Sprite * givenSprite){
	for (int i = 0; i < sprites.size(); i++) {
		//if the pointers are pointing at the same object
		if(sprites[i] == givenSprite){
			std::vector<Sprite*>::iterator spritesIterator = sprites.begin();
			delete sprites[i];
			sprites[i] = nullptr;
			sprites.erase(spritesIterator);
			return;
		}
	}
}