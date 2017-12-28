#include "stdafx.h"
#include "SoundManager.h"
#include "EngineConfig.h"

SoundManager::SoundManager(){
}


SoundManager::~SoundManager(){
}

bool SoundManager::initialize()
{
	int audio_result = Mix_OpenAudio(EngineConfig::AUDIO_FREQUENCY, EngineConfig::AUDIO_FORMAT, EngineConfig::AUDIO_CHANNELS, EngineConfig::AUDIO_CHUNKSIZE);

	if (audio_result == -1)
	{
		const char* error = Mix_GetError();
		return false;
	}

	Mix_Init(EngineConfig::AUDIO_FLAGS);

	return true;
}

void SoundManager::shutdown()
{
	Mix_CloseAudio();
	Mix_Quit();
}

Sound * SoundManager::createSound(const std::string givenFile)
{
	return nullptr;
}

void SoundManager::destroySound(Sound * givenSound)
{
}

Music * SoundManager::createMusic(const std::string givenFile)
{
	return nullptr;
}

void SoundManager::destroyMusic(Music * givenMusic)
{
}
