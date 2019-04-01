#ifndef TEXTURE
#define TEXTURE

#include <GL/glew.h>
#include "structs.h"

using namespace Textures;

class Texture {

	const char * const file;
	const PixelDataType dataType;

	int width, height;
	GLuint textureID;

	GLuint configure(const void* data, PixelDataType dataType) const;

public:

	/*
		Creates a new texture for the given file.
		@param file defines the absolute file path and name to the image.
		@param dataType tells OpenGL on how to interpret the image data.
	*/
	Texture(const char* file, PixelDataType dataType);
	~Texture() {};

	void prepare();

	/*
		Binds this texture, in order to draw it.
	*/
	void bind() const;

	int getWidth() const { return width; };
	int getHeight() const { return height; };

	/*
		Reads in the image data and parses it, so that OpenGL can handle it.
		@param rawImageData is the data read in without any parsing.
		@returns the parsed and OpenGL compatible image data.
	*/
	virtual TextureInfo readTexture(const unsigned char* rawImageData) const = 0;


};

#endif TEXTURE