#pragma once
class Sprite{
public:
	//TODO : Implement all of these (or remove them lmfaoooo)
	enum ORIGIN {
		CENTER,
		TOP_LEFT,
		BOTTOM_LEFT,
		TOP_RIGHT,
		BOTTOM_RIGHT
	};
	//givenx, y, h and w are optional. They default to 0
	Sprite(SDL_Texture* givenTexture, int givenX = 0, int givenY = 0, int givenH = 0, int givenW = 0);
	~Sprite();
	SDL_Rect getArea();
	SDL_Texture* getTexture();
	float getScale();
	double getAngle();
	int getHeight();
	int getWidth();
	SDL_Point getOrigin();
	SDL_RendererFlip getFlip();
	int getLayer();
	void setScale(float givenScale);
	void setAngle(double givenAngle);
	void setOrigin(int givenX, int givenY);
	void setOrigin(ORIGIN givenOrigin);
	void setFlip(SDL_RendererFlip givenFlip);
	void setLayer(int givenLayer);
private:
	SDL_Texture* myTexture = nullptr;
	SDL_Rect area;
	float scale = 1.0f;
	double angle = 0;
	SDL_Point origin = {0,0};
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	unsigned int layer = 0;
};

