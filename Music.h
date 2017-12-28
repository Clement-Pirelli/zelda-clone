#pragma once
class Music{
public:
	Music(Mix_Music* givenMusic);
	~Music();
	void play();
	void stop();
private:
	Mix_Music* myMusic;
	int myChannel;
};

