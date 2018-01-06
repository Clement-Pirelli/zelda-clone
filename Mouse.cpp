#include "stdafx.h"
#include "Mouse.h"


Mouse::Mouse(){
	//set every key as not pressed in the key arrays
	for (int i = 0; i < MAXBUTTONS; i++){
		buttons[i] = false;
		buttonsLastFrame[i] = false;
	}
}


Mouse::~Mouse(){
}

bool Mouse::isMouseButtonDown(int givenButton){
	if (givenButton >= MAXBUTTONS)
		return false;
	return buttons[givenButton];
}

bool Mouse::isMouseButtonPressed(int givenButton){
	if (givenButton >= MAXBUTTONS)
		return false;
	return (buttons[givenButton] == true
			&& buttonsLastFrame[givenButton] == false);
}

bool Mouse::isMouseButtonReleased(int givenButton){
	if (givenButton >= MAXBUTTONS)
		return false;
	return (buttons[givenButton] == false
			&& buttonsLastFrame[givenButton] == true);
}

SDL_Point Mouse::getMousePosition(){
	return position;
}

SDL_Point Mouse::getMouseMotion(){
	return motion;
}

void Mouse::handleEvents(SDL_Event & givenEvent){
	if (givenEvent.type == SDL_MOUSEBUTTONDOWN){
		setButton(givenEvent.button.button - 1, true);
	} else if (givenEvent.type == SDL_MOUSEBUTTONUP){
		setButton(givenEvent.button.button - 1, false);
	} else if (givenEvent.type == SDL_MOUSEMOTION){
		position.x = givenEvent.motion.x;
		position.y = givenEvent.motion.y;
		motion.x = givenEvent.motion.xrel;
		motion.y = givenEvent.motion.yrel;
	} else if (givenEvent.type == SDL_MOUSEWHEEL){
		//TODO: Implement functionality for mouse Wheel
	}
}

void Mouse::lateUpdate(float givenDeltaTime){
	for (int i = 0; i < MAXBUTTONS; i++){
		buttonsLastFrame[i] = buttons[i];
	}
}

void Mouse::setButton(int buttonIndex, bool givenValue){
	if (buttonIndex >= MAXBUTTONS)
		return;
	buttons[buttonIndex] = givenValue;
}
