#pragma once

#include "Reader.h"

class BmpReader : public Reader {


public:

	~BmpReader() {}

	TextureInfo readTexture(const unsigned char * const rawData, const Color* const alphaColor) const override;

};