#include "Vec2.h"

Vec2 Vec2::add(Vec2 vec) const {
	return Vec2(this->x + vec.x, this->y + vec.y);
}

Vec2 Vec2::sub(Vec2 vec) const {
	return Vec2(this->x - vec.x, this->y - vec.y);
}

Vec2 Vec2::mul(float scalar) const {
	return Vec2(this->x * scalar, this->y * scalar);
}

Vec2 Vec2::norm() const {
	if (length() == 0) {
		return Vec2();
	}

	return Vec2(this->x / length(), this->y / length());
}

float Vec2::length() const {
	return (float) sqrt(pow(this->x, 2) + pow(this->y, 2));
}

Vec2 Vec2::inv() const {
	return Vec2(-x, -y);
}

Vec2 Vec2::rotateTo(Vec2 vec, float length) const {
	Vec2 res = vec.sub(*this).norm().mul(length);

	return Vec2(res.x, res.y);
}

Vec2 Vec2::cross(const Vec2 vec) const {
	// a2 * b3 - a2 * b2
	// a3 * b1 - a1 * b3
	// a1 * b2 - a2 * b1
	// -----------------
	// a3 = b3 = 0
	// -----------------
	// -a2 * b2
	// a1 * b2 - a2 * b1

	return Vec2(-y * vec.y, x * vec.y - y * vec.x);
}

Vec2 Vec2::absolut() const {
	return Vec2(abs(x), abs(y));
}

Vec2 Vec2::getRotatedInstance(const int angleDeg) {
	const float x = 1;
	// atan(y/x) = alpha
	// tan(alpha) = y/x
	// => x * tan(alpha) = y

	float angleRad = (float) (angleDeg * M_PI / 180.0f);

	const float y = x * tan(angleRad);

	return Vec2(-cos(angleRad), -sin(angleRad)).norm();
}

float Vec2::getAngleToXAxis() const {
	return (float) ((atan(y / x) * 180.f) / M_PI);
}