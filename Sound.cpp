#include "stdafx.h"
#include "Sound.h"


Sound::Sound(Mix_Chunk* givenChunk){
	myChunk = givenChunk;
}

Sound::~Sound(){
}

void Sound::play(){
	myChannel = Mix_PlayChannel(-1, myChunk, 0);
}

void Sound::stop(){
	if (myChannel == -1){
		return;
	}
	if (Mix_Playing(myChannel)){
		Mix_HaltChannel(myChannel);
		myChannel = -1;
	}
}
