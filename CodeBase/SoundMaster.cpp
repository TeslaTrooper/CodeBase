#include "SoundMaster.h"

SoundMaster::SoundMaster() {
	initOpenAL();
}

void SoundMaster::initOpenAL() {
	ALCdevice *dev;
	ALCcontext *ctx;
	ALuint buffer;

	// Init device
	dev = alcOpenDevice(NULL);
	if (!dev)
		fprintf(stderr, "Unable to open device\n");

	// Create context and make it current
	ctx = alcCreateContext(dev, NULL);
	alcMakeContextCurrent(ctx);
	if (!ctx)
		fprintf(stderr, "Unable to create or set context\n");

	// Clear errors
	alGetError();

	alGenBuffers(1, &buffer);
	if (alGetError() == AL_NO_ERROR) {
		fprintf(stderr, "Unable to create buffer\n");
		alDeleteBuffers(1, &buffer);
	}


	WaveData waveData = WaveLoader().loadWAVFile("test.wav");

	ALenum format = waveData.format == Format::MONO16 ? AL_FORMAT_MONO16 : AL_FORMAT_STEREO16;

	alBufferData(buffer, format, waveData.data, waveData.chunkSize, waveData.rate);
	free(waveData.data);

	alGenSources(1, &source);
}

void SoundMaster::play() {
	alSourcePlay(source);
}