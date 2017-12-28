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

bool Keyboard::isKeyPressed(SDL_Scancode givenkey){
	return (keys[givenkey] == true && keysLastFrame[givenkey] == false);
}

bool Keyboard::isKeyDown(SDL_Scancode givenkey){
	return keys[givenkey];
}

bool Keyboard::isKeyReleased(SDL_Scancode givenkey){
	return false;
}

void Keyboard::lateUpdate(float deltatime){
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		keysLastFrame[i] = keys[i];
	}
}

void Keyboard::handleEvents(SDL_Event & givenevent){
	if (givenevent.type == SDL_KEYDOWN) {
		setKey(givenevent.key.keysym.scancode, true);
	} else {
		if (givenevent.type == SDL_KEYUP) {
			setKey(givenevent.key.keysym.scancode, false);
		}
	}
	
}

void Keyboard::setKey(SDL_Scancode givenkey, bool keyvalue){
	keys[givenkey] = keyvalue;
}
