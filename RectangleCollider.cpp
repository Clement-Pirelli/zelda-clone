#include "stdafx.h"
#include "RectangleCollider.h"


RectangleCollider::RectangleCollider(int givenX, int givenY, int givenW, int givenH){
	setPosition(givenX, givenY);
	setSize(givenW, givenH);
}

RectangleCollider::~RectangleCollider(){
}

SDL_Rect RectangleCollider::getRectangle(){
	return myBounds;
}

void RectangleCollider::setPosition(int givenX, int givenY){
	myBounds.x = givenX;
	myBounds.y = givenY;
}

void RectangleCollider::setSize(int givenW, int givenH){
	//we don't want negative or null sizes
	(givenW <= 0) ? (myBounds.w = 1) : (myBounds.w = givenW);
	(givenH <= 0) ? (myBounds.h = 1) : (myBounds.h = givenH);
}

void RectangleCollider::setSize(int givenW, int givenH, float givenScale){
	setSize(static_cast<int>(givenW * givenScale), static_cast<int>(givenH * givenScale));

}

COLLIDERTYPE RectangleCollider::getType(){
	return COLLIDERTYPE::RECTANGLE;
}
