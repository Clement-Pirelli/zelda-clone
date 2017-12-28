#pragma once
class Sound{
public:
	Sound(Mix_Chunk* givenChunk);
	~Sound();
	void play();
	void stop();
private:
	Mix_Chunk* myChunk;
	int myChannel;
};

