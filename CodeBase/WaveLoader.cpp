#include "WaveLoader.h"

WaveData WaveLoader::loadWAVFile(const char* const fileName) {
	FILE* file = File::open(fileName);

	// Defines a buffer with a usable size of 4 bytes (32 bit)
	// Last byte is reserved for terminal symbol (in order to use strcmp)
	char xbuffer[5];
	xbuffer[4] = '\0';

	// Read the first 4 bytes (ChunkID) into xbuffer
	// Check, if the content of xbuffer is equal to "RIFF"
	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "RIFF") != 0)
		throw "Not a WAV file";

	// Read next 4 byte as little endian (ChunkSize)
	file_read_int32_le(xbuffer, file);

	// Read next 4 bytes (Format) into xbuffer
	// Check, if the content of xbuffer is equal to "WAVE"
	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "WAVE") != 0)
		throw "Not a WAV file";

	// Read next 4 bytes (Subchunk1ID) into xbuffer
	// Check, if the content of xbuffer is equal to "fmt "
	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "fmt ") != 0)
		throw "Invalid WAV file";

	// Read next 4 bytes as little endian (Subchunk1Size)
	file_read_int32_le(xbuffer, file);

	// Read all properties
	short audioFormat = file_read_int16_le(xbuffer, file);
	short channels = file_read_int16_le(xbuffer, file);
	int sampleRate = file_read_int32_le(xbuffer, file);
	int byteRate = file_read_int32_le(xbuffer, file);
	file_read_int16_le(xbuffer, file);
	short bitsPerSample = file_read_int16_le(xbuffer, file);

	//if (audioFormat != 16) {
	if (false) {
		short extraParams = file_read_int16_le(xbuffer, file);
		file_ignore_bytes(extraParams, file);
	}

	if (fread(xbuffer, sizeof(char), 4, file) != 4 || strcmp(xbuffer, "data") != 0)
		throw "Invalid WAV file";

	int dataChunkSize = file_read_int32_le(xbuffer, file);
	unsigned char* bufferData = file_allocate_and_read_bytes(dataChunkSize, file);

	fclose(file);

	Format type = GetFormatFromInfo(channels, bitsPerSample);

	//float duration = float(dataChunkSize) / byteRate;
	return WaveData(type, bufferData, dataChunkSize, byteRate);
}

int WaveLoader::file_read_int32_le(char* const buffer, FILE* const file) {
	char tmpBuffer[4];

	fread(tmpBuffer, sizeof(char), 4, file);
	buffer[0] = tmpBuffer[3];
	buffer[1] = tmpBuffer[2];
	buffer[2] = tmpBuffer[1];
	buffer[3] = tmpBuffer[0];

	int a = (int) (((unsigned char) buffer[0]) << 24);
	int b = (int) (((unsigned char) buffer[1]) << 16);
	int c = (int) (((unsigned char) buffer[2]) << 8);
	int d = (int) (((unsigned char) buffer[3]));

	return a | b | c | d;
}

short WaveLoader::file_read_int16_le(char* const buffer, FILE* const file) {
	char tmpBuffer[2];

	fread(tmpBuffer, sizeof(char), 2, file);
	buffer[0] = tmpBuffer[1];
	buffer[1] = tmpBuffer[0];

	short highByte = (short) (((unsigned char) buffer[0]) << 8);
	short lowByte = (short) (((unsigned char) buffer[1]));

	return highByte | lowByte;
}

void WaveLoader::file_ignore_bytes(int count, FILE* file) {
	char* buffer = new char[count];

	fread(buffer, sizeof(char), count, file);
}

unsigned char* WaveLoader::file_allocate_and_read_bytes(int byteSize, FILE* file) {
	unsigned char* buffer = (unsigned char*) malloc((byteSize + 1) + sizeof(char));
	fread(buffer, byteSize, sizeof(char), file);

	return buffer;
}

Format WaveLoader::GetFormatFromInfo(short channels, short bitsPerSample) {
	return channels == 1 ? MONO16 : STEREO16;
}