#include "Mat4.h"

Mat4 Mat4::ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
	Mat4 projection;

	projection.elements.at(0).at(0) = 2.0f / (right - left);
	projection.elements.at(1).at(1) = 2.0f / (top - bottom);
	projection.elements.at(3).at(0) = -(right + left) / (right - left);
	projection.elements.at(3).at(1) = -(top + bottom) / (top - bottom);

	projection.elements.at(2).at(2) = -2.0f / (zFar - zNear);
	projection.elements.at(3).at(2) = -(zFar + zNear) / (zFar - zNear);

	return projection;
}

Mat4 Mat4::getTransformation(const Vec2 position, const Vec2 size) {
	Mat4 translation = Mat4::translate(position);
	Mat4 scaling = Mat4::scale(size);

	return translation.mul(scaling);
}

Mat4 Mat4::getTransformation(const Vec2 position, const Vec2 size, const float angleDeg, const Vec2 rotationPoint) {
	Mat4 translation = Mat4::translate(position);
	Mat4 scaling = Mat4::scale(size);
	Mat4 rotation = Mat4::rotateZ(angleDeg, rotationPoint);

	return translation.mul(scaling.mul(rotation));
}

Mat4 Mat4::rotateX(const float angleDeg) {
	Mat4 rotation;

	float angleRad = angleDeg * (float) M_PI / 180.0f;

	rotation.elements.at(1).at(1) = (float) cos(angleRad);
	rotation.elements.at(2).at(2) = (float) cos(angleRad);
	rotation.elements.at(1).at(2) = (float) -sin(angleRad);
	rotation.elements.at(2).at(1) = (float) sin(angleRad);

	return rotation;
}

Mat4 Mat4::rotateZ(const float angleDeg) {
	Mat4 rotation;

	float angleRad = angleDeg * (float) M_PI / 180.0f;

	rotation.elements.at(0).at(0) = (float) cos(angleRad);
	rotation.elements.at(1).at(1) = (float) cos(angleRad);
	rotation.elements.at(1).at(0) = (float) -sin(angleRad);
	rotation.elements.at(0).at(1) = (float) sin(angleRad);

	return rotation;
}

Mat4 Mat4::rotateZ(const float angleDeg, const Vec2 origin) {
	Mat4 translation = Mat4::translate(origin);
	Mat4 rotation = Mat4::rotateZ(angleDeg);
	Mat4 invTranslation = Mat4::translate(origin.inv());

	return translation.mul(rotation.mul(invTranslation));
}

Mat4 Mat4::translate(const Vec2 vec) {
	Mat4 translation;

	translation.elements.at(3).at(0) = vec.x;
	translation.elements.at(3).at(1) = vec.y;

	return translation;
}

Mat4 Mat4::scale(const Vec2 vec) {
	Mat4 scaling;

	scaling.elements.at(0).at(0) = vec.x;
	scaling.elements.at(1).at(1) = vec.y;

	return scaling;
}

Mat4 Mat4::mul(const Mat4 mat4) const {
	Mat4 result;

	for (int row = 0; row < 4; row++) {
		for (int column = 0; column < 4; column++) {
			float value = 0;

			for (int i = 0; i < 4; i++) {
				value += elements.at(i).at(row) * mat4.elements.at(column).at(i);
			}

			result.elements.at(column).at(row) = value;
		}
	}

	return result;
}

Vec2 Mat4::transform(const Vec2 vec) const {
	float x = elements.at(0).at(0) * vec.x + elements.at(1).at(0) * vec.y + elements.at(3).at(0);
	float y = elements.at(0).at(1) * vec.x + elements.at(1).at(1) * vec.y + elements.at(3).at(1);

	return Vec2(x, y);
}

const float* Mat4::ptr(const Mat4 mat) {
	return &(mat.elements.at(0).at(0));
}

Mat4::Mat4() {
	elements.at(0) = { 1.0f, 0.0f, 0.0f, 0.0f };
	elements.at(1) = { 0.0f, 1.0f, 0.0f, 0.0f };
	elements.at(2) = { 0.0f, 0.0f, 1.0f, 0.0f };
	elements.at(3) = { 0.0f, 0.0f, 0.0f, 1.0f };
}

Mat4::Mat4(array<array<float, 4>, 4> elements) {
	this->elements = elements;
}

Mat4::~Mat4() {}

