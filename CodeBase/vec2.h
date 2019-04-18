#ifndef VEC2
#define VEC2

#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>

class __declspec(dllexport) Vec2 {

public:

	float x;
	float y;

	Vec2() : x(0.f), y(0.f) {};
	Vec2(float x, float y) : x(x), y(y) {};
	Vec2(int x, int y) : Vec2((float) x, (float) y) {};
	Vec2(float x, int y) : Vec2(x, (float) y) {};
	Vec2(int x, float y) : Vec2((float) x, y) {};

	Vec2 add(const Vec2& vec) const;
	Vec2 sub(const Vec2& vec) const;
	Vec2 mul(const float scalar) const;
	Vec2 div(const float scalar) const;

	Vec2 absolut() const;

	/*
		Rotates this vector to a given point in 2D space and sets its length
		to the defined value.
		@param vec		defines the point in 2D space, were to rotate to.
		@param length	defines the length of the returned vector.
		@returns		the rotated and scaled vector.
	*/
	Vec2 rotateTo(const Vec2& vec, const float length) const;


	/*
		Norms the length to 1.
		@returns the normalized vector.
	*/
	Vec2 norm() const;


	/*
		Norms the length to the given length.
		@returns the normalized vector.
	*/
	Vec2 norm(const float length) const;


	/*
		Inverts all components of this vector.
		@returns the inverted vector.
	*/
	Vec2 inv() const;


	/*
		Calculates the cross-product of this and the given vector.
		@param vec	the second vector sued for cross-product.
		@returns	the cross-product of the two vectors.
	*/
	Vec2 cross(const Vec2& vec) const;
	
	float length() const;
	float getAngleToXAxis() const;


	/*
		Calculated a vector with length of 1 and a direction
		corresponding to the given angle.
		@param angleDeg		defines the angle, by which the vector gets rotated in degrees.
		@returns			the rotated vector.
	*/
	static Vec2 getRotatedInstance(const int angleDeg);

	bool operator==(const Vec2& vec) const { return vec.x == x && vec.y == y; };
	Vec2 operator+(const Vec2& vec) const { return add(vec); };
	Vec2 operator-(const Vec2& vec) const { return sub(vec); };
	Vec2 operator*(const float scalar) const { return mul(scalar); };
	Vec2 operator*(const int scalar) const { return mul((float) scalar); };
	Vec2 operator*(const Vec2& vec) const { return Vec2(x * vec.x, y * vec.y); };
	Vec2 operator/(const float scalar) const { return div(scalar); };
	Vec2 operator-() const { return inv(); };
	void operator=(const Vec2& vec) { x = vec.x; y = vec.y; };

};

#endif VEC2