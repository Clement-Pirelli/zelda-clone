#pragma once

//should only hold values relevant to configuring the engine
class EngineConfig {
public:
	static const char* WINDOW_TITLE;
	static const int WINDOW_WIDTH;
	static const int WINDOW_HEIGHT;


	// Audio
	static const int AUDIO_FLAGS;
	static const int AUDIO_FREQUENCY;
	static const Uint16 AUDIO_FORMAT;
	static const int AUDIO_CHANNELS;
	static const int AUDIO_CHUNKSIZE;

private:
	EngineConfig() = delete;
};
