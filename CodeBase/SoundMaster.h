#ifndef SOUND_MASTER
#define SOUND_MASTER

#include <AL/al.h>
#include <AL/alc.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <map>
#include <vector>

#include "WaveLoader.h"

#define PLAY_MODE_LOOP 1
#define PLAY_MODE_ONCE 2

class SoundMaster {

	ALCdevice* device;
	ALCcontext* context;

	map<int, ALuint> sources;
	vector<ALuint> buffers;

	void initOpenAL();
	bool isPlaying(ALuint source) const;
	bool isStopped(ALuint source) const;

public:

	SoundMaster();
	~SoundMaster();

	void load(int identifier, const char* const file);

	void play(int identifier, int mode, bool interrupt) const;
	void playBlocking(int identifier) const;

	void stop(int identifier) const;

};

#endif SOUND_MASTER