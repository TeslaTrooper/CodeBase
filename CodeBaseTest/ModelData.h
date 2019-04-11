#ifndef MODEL_DATA
#define MODEL_DATA

#include "../CodeBase/Entity.h"

#define VERTEX_COMP 2

using namespace Binding;

class TestEntity : public Entity {

	float scale;

	VertexData vertexData;
	IndexData indexData;

public:
	TestEntity(const Vec2& position, const float scale, const VertexData& vertexData, const IndexData& indexData) : Entity() {
		this->scale = scale;
		this->vertexData = vertexData;
		this->indexData = indexData;

		setPosition(position);

		updateTransformation();
	}

	bool canCollide() const override { return true; };
	bool canCollideWith(const Entity* const e) const override { return true; };
	void updateTransformation() override {
		setTransformation(Mat4::getTransformation(getPosition(), Vec2(scale, scale)));
	};
	VertexData getVertexData() const override { return vertexData; };
	IndexData getTriangulatedIndexData() const override { return indexData; };
};

namespace Sqaure {
	static const float* vertices = new float[8] { 0, 0, 0, 1, 1, 1, 1, 0 };
	static const int* indices = new int[6] { 0, 1, 2, 0, 2, 3 };

	static const VertexData vertexData(vertices, VERTEX_COMP, 4);
	static const IndexData indexData(indices, 6);

	inline Entity* create(const Vec2& position, const float scale) { return new TestEntity(position, scale, vertexData, indexData); };
}

namespace TriangleData {
	static const float* vertices = new float[6] { 0, 1.5, 2, 3, 2, 0 };
	static const int* indices = new int[3] { 0, 2, 1 };

	static const VertexData vertexData(vertices, VERTEX_COMP, 3);
	static const IndexData indexData(indices, 3);

	inline Entity* create(const Vec2& position, const float scale) { return new TestEntity(position, scale, vertexData, indexData); };
}

namespace Concave {
	static const float* vertices = new float[10] { 0, 0, 0, 3, 2.5, 3, 0.5, 1.5, 2.5, 0 };
	static const int* indices = new int[9] { 0, 3, 1, 1, 3, 2, 0, 4, 3 };

	static const VertexData vertexData(vertices, VERTEX_COMP, 5);
	static const IndexData indexData(indices, 9);

	inline Entity* create(const Vec2& position, const float scale) { return new TestEntity(position, scale, vertexData, indexData); };
}

namespace Convex {
	static const float* vertices = new float[10] { 0, 1, 0.5, 2, 2, 2.5, 2.5, 1, 1, 0 };
	static const int* indices = new int[9] { 4, 1, 0, 4, 2, 1, 4, 3, 2 };

	static const VertexData vertexData(vertices, VERTEX_COMP, 5);
	static const IndexData indexData(indices, 9);

	inline Entity* create(const Vec2& position, const float scale) { return new TestEntity(position, scale, vertexData, indexData); };
}

#endif MODEL_DATA