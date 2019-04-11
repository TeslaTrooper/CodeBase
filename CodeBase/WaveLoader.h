#ifndef WAVE_LOADER
#define WAVE_LOADER

#include "structs.h"

using namespace Sound;

class WaveLoader {

	int file_read_int32_le(char* const buffer, FILE* const file);
	short file_read_int16_le(char* const buffer, FILE* const file);
	void file_ignore_bytes(int count, FILE* file);
	unsigned char* file_allocate_and_read_bytes(int byteSize, FILE* file);
	Format GetFormatFromInfo(short channels, short bitsPerSample);

public:

	WaveData loadWAVFile(const char* const file);
};

#endif WAVE_LOADER