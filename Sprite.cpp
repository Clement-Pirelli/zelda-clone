#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(SDL_Texture* givenTexture, int givenX, int givenY, int givenW, int givenH){
	myTexture = givenTexture;
	area.x = givenX;
	area.y = givenY;
	area.w = givenW;
	area.h = givenH;
}

Sprite::~Sprite() {
}

SDL_Rect Sprite::getArea(){
	return area;
}

SDL_Texture* Sprite::getTexture(){
	return myTexture;
}

float Sprite::getScale(){
	return scale;
}

double Sprite::getAngle(){
	return angle;
}

int Sprite::getHeight(){
	return area.h;
}

int Sprite::getWidth(){
	return area.w;
}

SDL_Point Sprite::getOrigin(){
	return origin;
}

SDL_RendererFlip Sprite::getFlip(){
	return flip;
}

int Sprite::getLayer(){
	return layer;
}

void Sprite::setScale(float givenScale){
	scale = givenScale;
}

void Sprite::setAngle(double givenAngle){
	angle = givenAngle;
}

void Sprite::setOrigin(int givenX, int givenY){
	origin.x = givenX; 
	origin.y = givenY;
}

void Sprite::setOrigin(ORIGIN givenOrigin){
	switch (givenOrigin) {
		case ORIGIN::TOP_LEFT:
			origin.x = 0;
			origin.y = 0;
		break;
		case ORIGIN::CENTER:
			origin.x = static_cast<int>(getArea().w / 2);
			origin.y = static_cast<int>(getArea().h / 2);
		break;
	}
}

void Sprite::setFlip(SDL_RendererFlip givenFlip){
	flip = givenFlip;
}

void Sprite::setLayer(int givenLayer){
	layer = givenLayer;
}