#include "Mat3.h"

Mat3::Mat3() {
	elements.at(0) = { 1.0f, 0.0f, 0.0f };
	elements.at(1) = { 0.0f, 1.0f, 0.0f };
	elements.at(2) = { 0.0f, 0.0f, 1.0f };
}

Mat3::Mat3(array<array<float, 3>, 3> elements) {
	this->elements = elements;
}

Mat3 Mat3::translate(Vec2 vec) {
	elements.at(2).at(0) = vec.x;
	elements.at(2).at(1) = vec.y;
	elements.at(2).at(2) = 1.0f;

	return *this;
}

Mat3 Mat3::scale(Vec2 vec) {
	elements.at(0).at(0) *= vec.x;
	elements.at(1).at(1) *= vec.y;
	elements.at(2).at(2) *= 1.0f;

	return *this;
}

Mat3 Mat3::mul(const Mat3 mat3) const {
	Mat3 result;

	for (int row = 0; row < 3; row++) {
		for (int column = 0; column < 3; column++) {
			float value = 0;

			for (int i = 0; i < 3; i++) {
				value += elements.at(i).at(row) * mat3.elements.at(column).at(i);
			}

			result.elements.at(column).at(row) = value;
		}
	}

	return result;
}

Vec2 Mat3::getTranslation() const {
	return Vec2(elements.at(2).at(0), elements.at(2).at(1));
}

const float * Mat3::ptr(Mat3 mat) {
	return &(mat.elements.at(0).at(0));
}

Mat3::~Mat3() {}
