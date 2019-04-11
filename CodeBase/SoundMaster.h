#ifndef SOUND_MASTER
#define SOUND_MASTER

#include <AL/al.h>
#include <AL/alc.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>

#include "WaveLoader.h"

class SoundMaster {

	ALuint source;

	void initOpenAL();

public:

	SoundMaster();

	void play();

};

#endif SOUND_MASTER