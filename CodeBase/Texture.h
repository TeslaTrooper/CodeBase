#ifndef TEXTURE
#define TEXTURE

#include <GL/glew.h>
#include "BmpReader.h"

class Texture {

	Reader* reader;

	const char * const file;

	int width, height;
	Color* alphaColor;
	GLuint textureID;

	GLuint configure(const void* data) const;

public:


	/*
		Creates a new texture for the given file.

		@param file		defines the absolute file path and name to the image.
		@param dataType tells OpenGL on how to interpret the image data.
	*/
	Texture(const char * const file, Format format);
	~Texture();


	/*
		Reads in the image data and parses it, so that OpenGL can handle it.

		@param rawImageData is the data read in without any parsing.
		@returns the parsed and OpenGL compatible image data.
	*/
	void loadTexture();


	/*
		Binds this texture, in order to draw it.
	*/
	void bind() const;


	/*
		In order to have transparent textures with non-alpha images,
		this method allows to set an RGB value, which gets interpreted
		as transparent color when loading.

		@param rgb	defines the color to interpret as transparent.
	*/
	void setAlternativeAlphaColor(Color* const color) { this->alphaColor = color; };

	int getWidth() const { return width; };
	int getHeight() const { return height; };

};

#endif TEXTURE