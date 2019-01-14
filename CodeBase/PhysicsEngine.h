#ifndef PHYSICS_ENGINE
#define PHYSICS_ENGINE

#include <vector>
#include <utility>

#include "Entity.h"

using namespace std;
using namespace Binding;
using namespace PhysX;

struct CollisionCallback {
	virtual void resolveCollision(Entity* e1, Entity* e2, const Vec2& location) const = 0;
};

class PhysicsEngine {

	const CollisionCallback* const callback;

	void updatePosition(const vector<Entity*>& entities, const float dt) const;
	void updateVelocity(const vector<Entity*>& bodies, const float dt) const;
	void detectCollision(const vector<Entity*>& bodies, const float dt) const;

	Vec2* detectTrianglePointIntersection(const vector<Vec2>& vertices, const vector<Triangle>& triangles) const;
	bool detectTrianglePointIntersection(const Vec2& vertex, const Triangle& triangleconst) const;
	vector<Vec2> getTransformedVertices(const Binding::VertexData& vertexData, const Mat4& transformtion) const;
	vector<Triangle> convertVerticesToTriangles(const vector<Vec2>& vertices, const Binding::IndexData& indexData) const;

public:

	PhysicsEngine(const CollisionCallback* const callback) : callback(callback) {};

	/*
		Calling this method calculates all physics related stuff since last frame.
		This includes
			- movement
			- collision detection
			- and recalculation of movements.
		@param	bodies is a list defining all objects, which are affected by physics.
				For each single body out of the given list, the steps mentioned above
				gets processed.
		@param	dt defines the time since last frame in seconds.
	*/
	void update(const vector<Entity*>& bodies, const float dt) const;

};

#endif PHYSICS_ENGINE