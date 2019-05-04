#ifndef CAMERA
#define CAMERA

#include "Entity.h"

class Camera {

	const Vec2 viewport;
	const Entity* const target;

public:

	Camera(const Entity* const target, int width, int height) : target(target), viewport(Vec2(width, height)) {};

	Mat4 getTransformation() const {
		Vec2 targetPosition = target->getPosition();
		Vec2 camPosition = targetPosition - (viewport / 2) + (target->getBbox() / 2);

		return Mat4::translate(-camPosition);
	};

};

#endif CAMERA