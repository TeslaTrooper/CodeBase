#include "BmpReader.h"

TextureInfo BmpReader::readTexture(const unsigned char * const rawData, const Color* const alphaColor) const {
	const int width = *reinterpret_cast<const int*>(&rawData[18]);
	const int height = *reinterpret_cast<const int*>(&rawData[22]);

	int padding = 0;
	while ((width * 3 + padding) % 4 != 0) {
		padding++;
	}
	int widthnew = width * 3 + padding;

	unsigned char* ret = new unsigned char[width * 4 * height];

	for (int line = 0; line < height; line++) {
		for (int column = 0, retcolumn = 0; column < widthnew - padding; column += 3, retcolumn += 4) {
			int ri = line * (width * 4) + retcolumn;
			int gi = ri + 1;
			int bi = ri + 2;
			int ai = ri + 3;

			ret[ri] = rawData[line * widthnew + column + 54 + 2];
			ret[gi] = rawData[line * widthnew + column + 54 + 1];
			ret[bi] = rawData[line * widthnew + column + 54 + 0];

			if (alphaColor != nullptr && ret[ri] == alphaColor->r && ret[gi] == alphaColor->g && ret[bi] == alphaColor->b)
				ret[ai] = 0;
			else
				ret[ai] = 255;
		}
	}

	return TextureInfo(width, height, ret);
}
