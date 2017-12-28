#include "stdafx.h"
#include "InputManager.h"
#include "Keyboard.h"

InputManager::InputManager(){
	myKeyboard = new Keyboard;
}

InputManager::~InputManager(){
	delete myKeyboard;
	myKeyboard = nullptr;
}

bool InputManager::initialize(){
	return true;
}

void InputManager::shutdown(){
}

bool InputManager::isKeyPressed(SDL_Scancode givenKey){
	return myKeyboard->isKeyPressed(givenKey);
}

bool InputManager::isKeyDown(SDL_Scancode givenKey){
	return myKeyboard->isKeyDown(givenKey);
}

bool InputManager::isKeyReleased(SDL_Scancode givenKey){
	return myKeyboard->isKeyReleased(givenKey);
}

void InputManager::handleEvents(SDL_Event & givenEvent){ 
	myKeyboard->handleEvents(givenEvent);
}

void InputManager::lateUpdate(float deltaTime){
	myKeyboard->lateUpdate(deltaTime);
}