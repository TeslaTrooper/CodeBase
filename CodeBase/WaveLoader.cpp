#include "WaveLoader.h"

Sound::WaveData WaveLoader::loadWAVFile(const char* const fileName) {
	FILE* file = File::open(fileName);

	// Defines a buffer with a usable size of 4 bytes (32 bit)
	// Last byte is reserved for terminal symbol (in order to use strcmp)
	char xbuffer[5];
	xbuffer[4] = '\0';

	// Read the first 4 bytes (ChunkID) into xbuffer
	// Check, if the content of xbuffer is equal to "RIFF"
	if (File::readBytes(xbuffer, 4, file) != 4 || strcmp(xbuffer, "RIFF") != 0)
		throw "Not a WAV file";

	// Read next 4 byte as little endian (ChunkSize)
	file_read_int32_le(file);

	// Read next 4 bytes (Format) into xbuffer
	// Check, if the content of xbuffer is equal to "WAVE"
	if (File::readBytes(xbuffer, 4, file) != 4 || strcmp(xbuffer, "WAVE") != 0)
		throw "Not a WAV file";

	// Read next 4 bytes (Subchunk1ID) into xbuffer
	// Check, if the content of xbuffer is equal to "fmt "
	if (File::readBytes(xbuffer, 4, file) != 4 || strcmp(xbuffer, "fmt ") != 0)
		throw "Invalid WAV file";

	// Read next 4 bytes as little endian (Subchunk1Size)
	int subChunkSize = file_read_int32_le(file);

	// Skip 2 bytes
	if (subChunkSize > 16)
		fseek(file, sizeof(short), SEEK_CUR);

	// Read all properties
	short audioFormat = file_read_int16_le(file);
	short channels = file_read_int16_le(file);
	int sampleRate = file_read_int32_le(file);
	int byteRate = file_read_int32_le(file);
	file_read_int16_le(file);
	short bitsPerSample = file_read_int16_le(file);

	if (File::readBytes(xbuffer, 4, file) != 4 || strcmp(xbuffer, "data") != 0)
			throw "Invalid WAV file";

	int dataChunkSize = file_read_int32_le(file);
	unsigned char* bufferData = file_allocate_and_read_bytes(dataChunkSize, file);

	fclose(file);

	Sound::Format type = getFormat(channels, bitsPerSample);

	return Sound::WaveData(type, bufferData, dataChunkSize, byteRate);
}

int WaveLoader::file_read_int32_le(FILE* const file) {
	char tmpBuffer[4];

	File::readBytes(tmpBuffer, 4, file);

	int byte1 = (int) (((unsigned char) tmpBuffer[3]) << 24);
	int byte2 = (int) (((unsigned char) tmpBuffer[2]) << 16);
	int byte3 = (int) (((unsigned char) tmpBuffer[1]) << 8);
	int byte4 = (int) (((unsigned char) tmpBuffer[0]));

	return byte1 | byte2 | byte3 | byte4;
}

short WaveLoader::file_read_int16_le(FILE* const file) {
	char tmpBuffer[2];

	File::readBytes(tmpBuffer, 2, file);

	short byte1 = (short) (((unsigned char) tmpBuffer[1]) << 8);
	short byte2 = (short) (((unsigned char) tmpBuffer[0]));

	return byte1 | byte2;
}

unsigned char* WaveLoader::file_allocate_and_read_bytes(int byteSize, FILE* file) {
	unsigned char* buffer = (unsigned char*) malloc((byteSize) * sizeof(unsigned char));
	//unsigned char* buffer = new unsigned char[byteSize];
	File::readBytes(buffer, byteSize, file);

	return buffer;
}

Sound::Format WaveLoader::getFormat(short channels, short bitsPerSample) {
	if (channels == 1)
		return bitsPerSample == 8 ? Sound::MONO8 : Sound::MONO16;

	if (channels == 2)
		return bitsPerSample == 8 ? Sound::STEREO8 : Sound::STEREO16;

	return Sound::UNSUPPORTED;
}