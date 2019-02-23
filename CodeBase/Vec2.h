#ifndef VEC2
#define VEC2

#define _USE_MATH_DEFINES

#include <math.h>
#include <cmath>

class Vec2 {

public:

	static const int COMPONENTS = 2;

	float x;
	float y;

	/*
		Erzeugt einen neuen Vektor.
	*/
	Vec2() : x(0.f), y(0.f) {};

	/*
		Erzeugt einen neuen Vektor.

		@param x	ist die x-Komponente.
		@param y	ist die x-Komponente.
	*/
	Vec2(float x, float y) : x(x), y(y) {};
	Vec2(int x, int y) : Vec2((float) x, (float) y) {};
	Vec2(float x, int y) : Vec2((float) x, (float) y) {};
	Vec2(int x, float y) : Vec2((float) x, (float) y) {};


	/*
	Addiert zu diesem Vektor einen anderen Vektor.
	@pararm der Vektor, um den addiert wird.
	@return gibt die Summe aus beiden Vektoren zurück.
	*/
	Vec2 add(const Vec2& vec) const;


	/*
	Subtrahiert von diesem Vektor einen anderen Vektor.
	@pararm der Vektor, um den subtrahiert wird.
	@return gibt die Differenz aus beiden Vektoren zurück.
	*/
	Vec2 sub(const Vec2& vec) const;


	/*
	Multipliziert von diesem Vektor um einen anderen Vektor.
	@pararm der Vektor, um den multipliziert wird.
	@return gibt das Produkt aus beiden Vektoren zurück.
	*/
	Vec2 mul(const float scalar) const;

	Vec2 div(const float scalar) const;


	/*
	Führt eine 2D-Rotation durch. Dabei wird dieser Vektor als Startpunkt verwedent.
	@param vec ist der Zielpunkt, auf den der neue Vektor zeigen soll.
	@length gibt die Länge des neuen Vektors an.
	@return gibt einen Vektor zurück, der auf vec zeigt und die gegebene Länge besitzt.
	*/
	Vec2 rotateTo(const Vec2& vec, const float length) const;


	/*
	@return gibt den normierten Vektor zurück.
	*/
	Vec2 norm() const;

	/*
	@return gibt den auf length normierten Vektor zurück.
	*/
	Vec2 norm(const float length) const;


	/*
	@return gibt die Länge des Vektors zurück.
	*/
	float length() const;

	Vec2 inv() const;

	Vec2 cross(const Vec2& vec) const;

	Vec2 absolut() const;

	float getAngleToXAxis() const;

	static Vec2 getRotatedInstance(const int angleDeg);

	/*
	Vergleicht die xy-Komponenten zweier Vektoren auf Gleichheit.
	@return gibt true zurück, wenn die Komponenten gleich sind.
	*/
	bool operator==(const Vec2& vec) const { return vec.x == x && vec.y == y; };
	Vec2 operator+(const Vec2& vec) const { return add(vec); };
	Vec2 operator-(const Vec2& vec) const { return sub(vec); };
	Vec2 operator*(const float scalar) const { return mul(scalar); };
	Vec2 operator*(const Vec2& vec) const { return Vec2(x * vec.x, y * vec.y); };
	Vec2 operator/(const float scalar) const { return div(scalar); };
	Vec2 operator-() const { return inv(); };
	void operator=(const Vec2& vec) { x = vec.x; y = vec.y; };

};

#endif VEC2