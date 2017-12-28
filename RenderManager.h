#pragma once
#include <vector>
class Sprite;
class RenderManager{
public:
	RenderManager ();
	~RenderManager ();
	bool initialize();
	void shutdown();
	void clear();
	void present();
	void draw(Sprite* givensprite, int givenX, int givenY, int givenLayer = 1);
	void debugDrawRect(int givenX, int givenY, int givenW, int givenH);
	void debugDrawRect(SDL_Rect givenRect);
	void setCameraPosition(int givenX, int givenY);
	void addToCameraPosition(int givenX, int givenY);
	SDL_Point getCameraPosition();
	SDL_Renderer* getRenderer();
private:
	struct DrawData {
		Sprite* sprite;
		int x;
		int y;
		int layer;
	};
	std::vector<DrawData> myDrawData;
	std::vector<SDL_Rect> myDebugData;
	void drawData();
	void sortData();
	SDL_Window* myWindow = nullptr;
	SDL_Renderer* myRenderer = nullptr;
	SDL_Point cameraOffset = {0,0};
};