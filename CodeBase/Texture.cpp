#include "Texture.h"

Texture::Texture(const char * file, PixelDataType dataType) : file(file), dataType(dataType) {}

void Texture::prepare() {
	const unsigned char* rawData = File::read(file);

	TextureInfo info = readTexture(rawData);
	width = info.width;
	height = info.height;

	textureID = configure(info.parsedData, dataType);
}

void Texture::bind() const {
	glBindTexture(GL_TEXTURE_2D, textureID);
}

GLuint Texture::configure(const void* data, PixelDataType dataType) const {
	GLuint id;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, dataType, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}