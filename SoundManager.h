#pragma once
#include <string>
#include <vector>
#include <map>

class Sound;
class Music;

class SoundManager{
public:
	SoundManager();
	~SoundManager();
	bool initialize();
	void shutdown();
	Sound* createSound(const std::string givenFile);
	void destroySound(Sound* givenSound); 
	Music* createMusic(const std::string givenFile);
	void destroyMusic(Music* givenMusic);
private:
	std::vector<Sound*> sounds;
	std::map<std::string, Mix_Chunk*> soundChunks;
	std::vector<Music*> musics;
	std::map<std::string, Mix_Chunk*> musicChunks;
};

