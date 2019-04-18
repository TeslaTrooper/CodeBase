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

class SoundDriver {

	ALCdevice* device;
	ALCcontext* context;

	map<int, ALuint> sources;
	vector<ALuint> buffers;

	void initOpenAL();
	bool isPlaying(ALuint source) const;
	bool isStopped(ALuint source) const;

public:

	__declspec(dllexport) SoundDriver();
	__declspec(dllexport) ~SoundDriver();


	/*
		Loads a specific sound file and connects it to the given identifier.
		@param identifier	is used to identify the sound later.
		@param file			specifies a path including filename to load.
	*/
	__declspec(dllexport) void load(int identifier, const char* const file);


	/*
		Plays a sound in a specific mode.
		@param identifier		specifies the sound to play.
		@param mode				specifices, if the sound should be played once, or in loop mode.
		@param interruptable	if true, then multiple calls for the same sound will
								interrupt the sound and start it from the beginning.
	*/
	__declspec(dllexport) void play(int identifier, int mode, bool interruptable) const;


	/*
		Stops a currently playing sound.
		@param	defines the sound to stop.
	*/
	__declspec(dllexport) void stop(int identifier) const;


	/*
		Calls play(...) implicitly and waits until the sound has finished playing.
		Only for testing purpose.
		@param identifier	defines the sound to play.
	*/
	__declspec(dllexport) void playBlocking(int identifier) const;

};

#endif SOUND_MASTER