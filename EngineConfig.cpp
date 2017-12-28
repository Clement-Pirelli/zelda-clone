#include "stdafx.h"
#include "EngineConfig.h"

const char* EngineConfig::WINDOW_TITLE = "Tiberius Engine";
const int EngineConfig::WINDOW_WIDTH = 640;
const int EngineConfig::WINDOW_HEIGHT = 480;

const int EngineConfig::AUDIO_FLAGS = MIX_INIT_MP3;
const int EngineConfig::AUDIO_FREQUENCY = 44100;
const Uint16 EngineConfig::AUDIO_FORMAT = MIX_DEFAULT_FORMAT;
const int EngineConfig::AUDIO_CHANNELS = 2;
const int EngineConfig::AUDIO_CHUNKSIZE = 1024;