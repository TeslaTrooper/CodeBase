#include "PhysicsEngine.h"

void PhysicsEngine::update(const vector<Entity*>& entities, const float dt) const {
	updatePosition(entities, dt);
	detectCollision(entities, dt);
	updateVelocity(entities, dt);
}

void PhysicsEngine::updatePosition(const vector<Entity*>& entities, const float dt) const {
	for each (Entity* e in entities) {
		// Fetch all data for physx calculations
		Vec2 position = e->getPosition();
		Vec2 movement = e->getMovement();

		// update position: pn = pn-1+vn-1
		e->setPosition(position + movement);
	}
}

void PhysicsEngine::updateVelocity(const vector<Entity*>& entities, const float dt) const {
	for each (Entity* e in entities) {
		// Fetch all data for physx calculations
		Vec2 movement = e->getMovement();
		Vec2 direction = e->getDirection();
		float acceleration = e->getAcceleration();
		float vmax = e->getVMax();

		// Friction is an acceleration pointing in the opposite direction of current movement
		Vec2 friction = -movement * 0.5f;
		// And we have the normal acceleration, which is triggered by player input
		Vec2 directionalAcceleration = direction * acceleration;
		// Sum up all accelerations
		Vec2 resultAcceleration = friction + directionalAcceleration;

		// We want to know delta movement (step) since last frame
		// => dV = a * t
		Vec2 deltaMovement = resultAcceleration * dt;
		// We want to know the overall movement
		// => V = a * t + V0 = dV + V0
		Vec2 tmpMovement = movement + deltaMovement;

		float currentSpeed = tmpMovement.length();
		// To prevent the ship from endless acceleration, we have to cap movement to vmax
		// Cap value is based on current speed and the maximum speed the object can have
		// Therefore, the resulting cap value is min(vmax, currentSpeed)
		float capValue = CustomMath::min(currentSpeed, vmax);

		// Cap velocity based on capValue
		Vec2 resultMovement = tmpMovement.norm() * capValue;

		// Finally, pass updated velocity vector to object
		e->setMovement(resultMovement);
	}
}

void PhysicsEngine::detectCollision(const vector<Entity*>& entities, const float dt) const {
	// What we need:
	// VertexData from each object
	// IndexData defining triangles based on VertexData
	// Transformation matrix for transforming each single vertex to its actual position on screen

	vector<vector<Vec2>> transformedVertices;
	vector<vector<Triangle>> transformedTriangles;

	for each (Entity* e in entities) {
		VertexData vertexData = e->getVertexData();
		Mat4 transformation = e->getTransformation();
		vector<Vec2> vertices = getTransformedVertices(vertexData, transformation);

		IndexData indexData = e->getTriangulatedIndexData();
		vector<Triangle> triangles = convertVerticesToTriangles(vertices, indexData);

		transformedVertices.push_back(vertices);
		transformedTriangles.push_back(triangles);
	}

	for (int outerIndex = 0; outerIndex < entities.size(); outerIndex++) {
		Entity* outerEntity = entities.at(outerIndex);

		if (!outerEntity->canCollide())
			continue;

		for (int innerIndex = 0; innerIndex < entities.size(); innerIndex++) {
			Entity* innerEntity = entities.at(innerIndex);

			if (innerIndex == outerIndex)
				continue;

			if (!innerEntity->canCollide())
				continue;

			if (!outerEntity->canCollideWith(innerEntity))
				continue;

			// At this point, a collision detection between innerEntity
			// and outerEntity is allowed.

			Vec2* collisionLocation = detectTrianglePointIntersection(transformedVertices.at(outerIndex), transformedTriangles.at(innerIndex));
			if (collisionLocation == nullptr)
				continue;

			printf("Collision at (%f|%f)\n", collisionLocation->x, collisionLocation->y);

			// Now, we know, if innerEntity is colliding with outerEntity
			callback->resolveCollision(innerEntity, outerEntity, *collisionLocation);

			delete collisionLocation;
		}
	}
}

Vec2* PhysicsEngine::detectTrianglePointIntersection(const vector<Vec2>& vertices, const vector<Triangle>& triangles) const {
	for each (Vec2 vertex in vertices) {
		for each (Triangle triangle in triangles) {
			bool hasIntersection = detectTrianglePointIntersection(vertex, triangle);

			if (hasIntersection)
				return new Vec2(vertex.x, vertex.y);
		}
	}

	return nullptr;
}

// Source: http://www.jeffreythompson.org/collision-detection/tri-point.php
// Source: https://www.youtube.com/watch?v=HYAgJN3x4GA
bool PhysicsEngine::detectTrianglePointIntersection(const Vec2& vertex, const Triangle& triangle) const {
	Vec2 a = triangle.p1;
	Vec2 b = triangle.p2;
	Vec2 c = triangle.p3;

	double zaehler1 = a.x * (c.y - a.y) + (vertex.y - a.y) * (c.x - a.x) - vertex.x * (c.y - a.y);
	double nenner1 = (b.y - a.y) * (c.x - a.x) - (b.x - a.x) * (c.y - a.y);
	double w1 = zaehler1 / nenner1;

	double zaehler2 = vertex.y - a.y - w1 * (b.y - a.y);
	double nenner2 = c.y - a.y;
	double w2 = zaehler2 / nenner2;

	return w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1;
}

vector<Vec2> PhysicsEngine::getTransformedVertices(const Binding::VertexData& vertexData, const Mat4& transformation) const {
	vector<Vec2> transformedVertices;

	for (int i = 0; i < vertexData.count * 2; i += Vec2::COMPONENTS) {
		Vec2 tmpVec = Vec2(vertexData.vertices[i], vertexData.vertices[i + 1]);
		transformedVertices.push_back(transformation.transform(tmpVec));
	}

	return transformedVertices;
}

vector<Triangle> PhysicsEngine::convertVerticesToTriangles(const vector<Vec2>& vertices, const Binding::IndexData& indexData) const {
	if (indexData.count % 3 != 0) {
		printf("Wrong arguments! Unable create triangles.");
		return vector<Triangle>();
	}

	vector<Triangle> triangles;
	for (int i = 0; i < indexData.count; i += 3) {
		Vec2 p1 = vertices.at(indexData.indices[i]);
		Vec2 p2 = vertices.at(indexData.indices[i + 1]);
		Vec2 p3 = vertices.at(indexData.indices[i + 2]);

		triangles.push_back({ p1, p2, p3 });
	}

	return triangles;
}