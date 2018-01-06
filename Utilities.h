#pragma once
#include <random>
namespace Utilities {
	//random generation function courtesy of Ulf Benjaminsson
	static int random(int min, int max) {
		static std::random_device rd; //obtain a random seed from hardware
		static std::mt19937 eng(rd()); //seed the generator
		std::uniform_int_distribution<> distr(min, max); //define the range
		return distr(eng);
	}
	
	static unsigned int getLength(int givenNumber){
		int length = 0;
		while (givenNumber >= 1){
			length++;
			givenNumber /= 10;
		}
		return length;
	}

}