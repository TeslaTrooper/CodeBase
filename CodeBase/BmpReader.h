#pragma once

#include "Reader.h"

class BmpReader : public Reader {


public:

	TextureInfo readTexture(const unsigned char * const rawData, const Color* const alphaColor) const override;

};