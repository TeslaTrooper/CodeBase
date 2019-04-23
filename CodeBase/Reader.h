#pragma once

#include "structs.h"

using namespace Textures;

struct Reader {

	virtual TextureInfo readTexture(const unsigned char * const rawData, const Color* const alphaColor) const = 0;

};