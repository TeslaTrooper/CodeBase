#ifndef CAMERA
#define CAMERA

#include "Entity.h"

class Camera {

	const Vec2 viewport;
	const Entity* target;

	const Mat4* recentTransformation;

	struct Transformation {
		Vec2 targetPosition;
		Vec2 camPosition;
	};
	Transformation* transformation;

public:

	Camera(const Entity* const target, int width, int height) : target(target), viewport(Vec2(width, height)), transformation(new Transformation()) {};

	Mat4 getTransformation() const {
		if (target != nullptr) {
			transformation->targetPosition = target->getPosition();
			transformation->camPosition = transformation->targetPosition - (viewport / 2) + (target->getBbox() / 2);
		}

		return Mat4::translate(-transformation->camPosition);
	};

	void updateTarget(const Entity* const target) {
		this->target = target;
	}

};

#endif CAMERA