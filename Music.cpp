#include "stdafx.h"
#include "Music.h"


Music::Music(Mix_Music * givenMusic){
	myMusic = givenMusic;
}

Music::~Music(){
}

void Music::play(){
	Mix_PlayMusic(myMusic, 0);
}

void Music::stop(){
	if (Mix_PlayingMusic()){
		Mix_HaltMusic();
	}
}