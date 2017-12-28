#pragma once
#include "Collider.h"

class RectangleCollider : public Collider{
public:
	RectangleCollider(int givenX, int givenY, int givenW, int givenH);
	~RectangleCollider();
	SDL_Rect getRectangle();
	void setPosition(int givenX, int givenY);
	void setSize(int givenW, int givenH);
	void setSize(int givenW, int givenH, float givenScale);
	COLLIDERTYPE getType();
private:
	SDL_Rect myBounds;
};

