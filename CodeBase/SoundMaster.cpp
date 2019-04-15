#include "SoundMaster.h"

SoundMaster::SoundMaster() {
	initOpenAL();
}

SoundMaster::~SoundMaster() {
	// delete sources
	for (const pair<int, ALuint>& source : sources)
		alDeleteSources(1, &source.second);

	//delete our buffer
	for (int i = 0; i < buffers.size(); i++)
		alDeleteBuffers(1, &buffers.at(i));

	context = alcGetCurrentContext();

	//Get device for active context
	device = alcGetContextsDevice(context);

	//Disable context
	alcMakeContextCurrent(NULL);

	//Release context(s)
	alcDestroyContext(context);

	//Close device
	alcCloseDevice(device);
}

void SoundMaster::initOpenAL() {
	// Init device
	device = alcOpenDevice(NULL);
	if (!device)
		fprintf(stderr, "Unable to open device\n");

	// Create context and make it current
	context = alcCreateContext(device, NULL);
	alcMakeContextCurrent(context);
	if (!context)
		fprintf(stderr, "Unable to create or set context\n");

	// Clear errors
	alGetError();
}

void SoundMaster::load(int identifier, const char* const file) {
	ALuint buffer, source;

	alGenBuffers(1, &buffer);
	buffers.push_back(buffer);

	// Create source
	alGenSources(1, &source);
	sources[identifier] = source;

	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	alSource3f(source, AL_POSITION, 0.0f, 0.0f, 0.0f);

	WaveData waveData = WaveLoader().loadWAVFile(file);
	alBufferData(buffer, (ALenum) waveData.format, (ALvoid*) waveData.data, waveData.chunkSize, waveData.rate);

	// Connect source to buffer
	alSourcei(source, AL_BUFFER, buffer);


	// Wave data is now transferred to OpenAL
	// => We can therefore delete the data
	free(waveData.data);
}

void SoundMaster::play(int identifier, int mode, bool interrupt) const {
	ALuint source = sources.at(identifier);

	if (!interrupt && isPlaying(source))
		return;

	alSourcei(source, AL_LOOPING, mode == PLAY_MODE_LOOP);
	alSourcePlay(source);
}

void SoundMaster::playBlocking(int identifier) const {
	play(identifier, PLAY_MODE_LOOP, false);

	ALint state;
	do {
		alGetSourcei(sources.at(identifier), AL_SOURCE_STATE, &state);
	} while (state != AL_STOPPED);
}

void SoundMaster::stop(int identifier) const {
	ALuint source = sources.at(identifier);

	if (isStopped(source))
		return;

	alSourceStop(source);
}

bool SoundMaster::isPlaying(ALuint source) const {
	ALint state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);

	return state == AL_PLAYING;
}

bool SoundMaster::isStopped(ALuint source) const {
	ALint state;
	alGetSourcei(source, AL_SOURCE_STATE, &state);

	return state == AL_STOPPED;
}