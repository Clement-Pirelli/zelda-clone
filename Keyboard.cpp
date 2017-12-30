#include "stdafx.h"
#include "Keyboard.h"


Keyboard::Keyboard(){
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		keys[i] = false;
		keysLastFrame[i] = false;
	}
}


Keyboard::~Keyboard(){
}

bool Keyboard::isKeyPressed(SDL_Scancode givenKey){
	return (keys[givenKey] == true && keysLastFrame[givenKey] == false);
}

bool Keyboard::isKeyDown(SDL_Scancode givenKey){
	return keys[givenKey];
}

bool Keyboard::isKeyReleased(SDL_Scancode givenKey){
	return (keys[givenKey] == false && keysLastFrame[givenKey] == true);
}

void Keyboard::lateUpdate(float givenDeltaTime){
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		keysLastFrame[i] = keys[i];
	}
}

void Keyboard::handleEvents(SDL_Event & givenEvent){
	if (givenEvent.type == SDL_KEYDOWN) {
		setKey(givenEvent.key.keysym.scancode, true);
	} else {
		if (givenEvent.type == SDL_KEYUP) {
			setKey(givenEvent.key.keysym.scancode, false);
		}
	}
	
}

void Keyboard::setKey(SDL_Scancode givenKey, bool keyValue){
	keys[givenKey] = keyValue;
}
