#include "stdafx.h"
#include "Engine.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "StateManager.h"
#include "Sprite.h"
#include "Service.h"
#include "BOTTOMTEXT_Entity.h"
#include "BOTTOMTEXT_State.h"
#include "StateOwner.h"
#include "SoundManager.h"
#include "EngineConfig.h"
#include <iostream>
#include <cassert>

Engine::Engine(){
	myRenderManager = new RenderManager();
	myInputManager = new InputManager();
	mySpriteManager = new SpriteManager();
	myStateManager = new StateManager();
	mySoundManager = new SoundManager();
	Service<SpriteManager>::setService(mySpriteManager);
	Service<InputManager>::setService(myInputManager);
	Service<RenderManager>::setService(myRenderManager);
	Service<SoundManager>::setService(mySoundManager);
}


Engine::~Engine(){
	Service<SoundManager>::setService(nullptr);
	delete mySoundManager;
	mySoundManager = nullptr;
	delete myStateManager;
	myStateManager = nullptr;
	Service<SpriteManager>::setService(nullptr);
	delete mySpriteManager;
	mySpriteManager = nullptr;
	Service<InputManager>::setService(nullptr);
	delete myInputManager;
	myInputManager = nullptr;
	Service<RenderManager>::setService(nullptr);
	delete myRenderManager;
	myRenderManager = nullptr;
}

void Engine::initialize(){
	int resultInit = SDL_Init(SDL_INIT_EVERYTHING);
	assert(resultInit == 0 && "SDL_Init failed!");

	SDL_Init(EngineConfig::AUDIO_FLAGS);

	int resultImage = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	assert(resultImage != 0 && "Image initialization failed!");

	bool resultRenderManager = false;
	resultRenderManager = myRenderManager->initialize();
	assert(resultRenderManager == true && "Render Manager initialization failed!");

	bool resultInputManager = myInputManager->initialize();
	assert(resultInputManager == true && "Input manager initialization failed!");

	bool resultSpriteManager = mySpriteManager->initialize(myRenderManager);
	assert(resultSpriteManager == true && "Sprite manager initialization failed");
}

void Engine::shutdown(){
	myInputManager->shutdown();
	myRenderManager->shutdown();
	mySpriteManager->shutdown();
	mySoundManager->shutdown();
	IMG_Quit();
	SDL_Quit();
}

void Engine::run(){
	running = true;
	StateOwner myStateOwner(*myStateManager);
	while (running){
		handleEvents();
		myRenderManager->clear();
		calculateDeltaTime();
		if (myStateManager->update(deltaTime) == false){
			running = false;
		}
		myInputManager->lateUpdate(deltaTime);
		myRenderManager->present();
		SDL_Delay(16);
	}
}

void Engine::handleEvents(){
	SDL_Event event;
	while (SDL_PollEvent(&event) == 1) {
		if (event.type == SDL_QUIT) {
			running = false;
		} else {
			myInputManager->handleEvents(event);
		}
	}
}

void Engine::calculateDeltaTime (){
	unsigned int tickCount = SDL_GetTicks();
	deltaTime = (tickCount - lastTickCount) * 0.001f;
	lastTickCount = SDL_GetTicks();
}
