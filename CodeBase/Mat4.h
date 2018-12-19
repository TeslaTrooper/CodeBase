#ifndef MAT4
#define MAT4

#define _USE_MATH_DEFINES 

#include <array>
#include <cmath>

#include "Vec2.h"

using namespace std;

class Mat4 {
	// Index with elements.at(col).at(row)
	array<array<float, 4>, 4> elements;

public:

	/*
	Erzeugt eine 4x4 Einheitsmatrix.
	*/
	Mat4();


	/*
	Erzeugt eine 4x4 Matrix mit den gegeben Elementen.
	*/
	Mat4(array<array<float, 4>, 4> elements);

	Mat4 mul(const Mat4 mat4) const;

	Vec2 transform(const Vec2 vec) const;

	/*
	Erzeugt eine orthographische Projektionsmatrix.
	@param left ist linke Rand.
	@param right ist der rechte Rand.
	@param bottom ist der untere Rand.
	@param top ist der obere Rand.
	@param zNear gibt den minimalen Z-Wert an, für den ein Objekt noch sichtbar ist.
	@param zFar gibt den maximalen Z-Wert an, für den ein Objekt noch sichtbar ist.
	@return gibt eine orthographische Projektionsmatrix zurück.
	*/
	static Mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);

	static Mat4 getTransformation(const Vec2 position, const Vec2 size);

	static Mat4 getTransformation(const Vec2 position, const Vec2 size, const float angleDeg, const Vec2 rotationPoint);

	static Mat4 rotateX(const float angleDeg);

	static Mat4 rotateZ(const float angleDeg);

	static Mat4 rotateZ(const float angleDeg, const Vec2 origin);

	/*
	Erzeugt eine Translationsmatrix.
	@param vec ist der Vektor, der die Translation angibt.
	@return gibt die Translationsmatrix zurück.
	*/
	static Mat4 translate(const Vec2 vec);

	/*
	Erzeugt eine Skalierungsmatrix.
	@param vec ist der Vektor, der die Skalierung angibt.
	@return gibt die Skalierungsmatrix zurück.
	*/
	static Mat4 scale(const Vec2 vec);


	/*
	@return gibt den Pointer, der auf das 1. Element zeigt, zurück.
	*/
	static const float* ptr(const Mat4 mat);

	~Mat4();
};

#endif MAT4