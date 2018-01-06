#pragma once
#include <array>
#include <string>

class Sprite;
class RenderManager;

class NumberFont {
public:
	NumberFont(std::string givenFilePath, int givenSpriteWidth, int givenSpriteHeight);
	~NumberFont();
	void render(SDL_Point givenCoordinates, int givenNumber);
private:
	SDL_Point numberDimensions{};
	std::array<Sprite*, 10> font;
	RenderManager* myRenderManager;
	std::string filePath = "../Assets/numbers_font.png";
};