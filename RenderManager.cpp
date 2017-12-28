#include "stdafx.h"
#include "RenderManager.h"
#include "Sprite.h"
#include "EngineConfig.h"
#include <cassert>
#include <iostream>

RenderManager::RenderManager(){
}

RenderManager::~RenderManager(){
}

bool RenderManager::initialize(){
	myWindow = SDL_CreateWindow(EngineConfig::WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, EngineConfig::WINDOW_WIDTH, EngineConfig::WINDOW_HEIGHT, 0);
	if (myWindow == nullptr) {
		return false;
	}
	myRenderer = SDL_CreateRenderer(myWindow, -1, SDL_RENDERER_ACCELERATED);
	if (myRenderer == nullptr) {
		return false;
	}
	return true;
}

void RenderManager::shutdown(){
	SDL_DestroyRenderer(myRenderer);
	myRenderer = nullptr;
	SDL_DestroyWindow(myWindow);
	myWindow = nullptr;
}

void RenderManager::clear(){
	SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 255); 
	SDL_RenderClear(myRenderer);
}

void RenderManager::present(){
	sortData();
	drawData();
	SDL_RenderPresent(myRenderer);
}

void RenderManager::drawData() {
	for (DrawData data : myDrawData) {
		SDL_Rect dst{
			data.x + cameraOffset.x,
			data.y + cameraOffset.y,
			static_cast<int>(data.sprite->getWidth() * data.sprite->getScale()),
			static_cast<int>(data.sprite->getHeight() * data.sprite->getScale())
		};
		SDL_RenderCopyEx(myRenderer,
						data.sprite->getTexture(),
						&data.sprite->getArea(),
						&dst, data.sprite->getAngle(),
						&data.sprite->getOrigin(),
						data.sprite->getFlip()
		);
	}
	myDrawData.clear();
	SDL_SetRenderDrawColor(myRenderer, 0, 255, 0, 255);
	for (SDL_Rect data : myDebugData){
		SDL_RenderDrawRect(myRenderer, &data);
	}
	myDebugData.clear();
	SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 0);
}

void RenderManager::sortData(){
	//original pseudocode by Henrik Warpefelt
	for (int i = 1; i < myDrawData.size(); ++i) {
		int j = i;
		while (j > 0 && myDrawData[j].layer < myDrawData[j - 1].layer) {
			//swap the DrawDatas
			DrawData tempData = myDrawData[j - 1];
			myDrawData[j - 1] = myDrawData[j];
			myDrawData[j] = tempData;
			j--;
		}
	}
}

void RenderManager::draw(Sprite* givenSprite, int givenX, int givenY, int givenLayer){
		myDrawData.push_back(DrawData{givenSprite, givenX, givenY, givenLayer});
}

void RenderManager::debugDrawRect (int givenX, int givenY, int givenW, int givenH){

	SDL_Rect tempRect;
	tempRect.x = givenX;
	tempRect.y = givenY;
	tempRect.w = givenW;
	tempRect.h = givenH;
	debugDrawRect(tempRect);
}

void RenderManager::debugDrawRect(SDL_Rect givenRect){
	givenRect.x += cameraOffset.x;
	givenRect.y += cameraOffset.y;
	myDebugData.push_back(givenRect);
}

void RenderManager::setCameraPosition(int givenX, int givenY){
	cameraOffset.x = givenX;
	cameraOffset.y = givenY;
}

SDL_Point RenderManager::getCameraPosition()
{
	return cameraOffset;
}

void RenderManager::addToCameraPosition(int givenX, int givenY)
{
	cameraOffset.x += givenX;
	cameraOffset.y += givenY;
}

SDL_Renderer* RenderManager::getRenderer(){
	return myRenderer;
}
