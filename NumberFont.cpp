#include "stdafx.h"
#include "NumberFont.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "RenderManager.h"
#include "Service.h"
#include "Utilities.h"
#include <vector>

NumberFont::NumberFont(std::string givenFilePath, int givenSpriteWidth, int givenSpriteHeight){
	filePath = givenFilePath;
	numberDimensions.x = givenSpriteHeight;
	numberDimensions.y = givenSpriteWidth;
	myRenderManager = Service<RenderManager>::getService();
	SpriteManager* tempSM = Service<SpriteManager>::getService();
	for (unsigned int i = 0; i < font.size(); i++){
		font[i] = tempSM->createSprite(filePath, numberDimensions.x * i, 0, numberDimensions.x, numberDimensions.y);
	}
}


NumberFont::~NumberFont(){
	for (Sprite* s : font){
		Service<SpriteManager>::getService()->destroySprite(s);
		s = nullptr;
	}
	myRenderManager = nullptr;
}

void NumberFont::render(SDL_Point givenCoordinates, int givenNumber){
	unsigned int length = Utilities::getLength(givenNumber);
	int n = givenNumber;
	if (n == 0){
		myRenderManager->draw(font[0], givenCoordinates.x, givenCoordinates.y);
		return;
	}
	std::vector<int> digits;
	for (unsigned int i = 0; i < length; i++){
		digits.push_back(n % 10);
		n /= 10;
	}
	for (unsigned int i = length; i > 0; i--){
			myRenderManager->draw(font[digits[i - 1]], givenCoordinates.x + (length - i) * numberDimensions.x, givenCoordinates.y);
	}
}