#pragma once

#include "Vec2.h"
#include "Mat4.h"

namespace Binding {

	struct IndexData {
		const int* indices;
		int count;

		IndexData() : IndexData(nullptr, 0) {}
		IndexData(const int* indices, int count) : indices(indices), count(count) {}
	};

	struct VertexData {
		const float* vertices;
		int componentCount;
		int count;

		VertexData() : VertexData(nullptr, 0, 0) {}
		VertexData(const float* vertices, int componentCount, int count) : vertices(vertices), componentCount(componentCount), count(count) {}
	};

	struct AttributeData {
		const int* attributeSizes;
		int count;
	};

	struct Bindable {
		VertexData vertexData;
		IndexData indexData;
		AttributeData attributeData;
	};

	struct RenderData {
		unsigned int vao;
		unsigned int ebo;
		unsigned int vbo;
		int indexCount, drawMode;
	};

	struct ScreenQuad {
		unsigned int vao, vbo;
	};

	struct FrameBuffer {
		unsigned int id;
		unsigned int textureAttachment;
		ScreenQuad screenQuad;

		FrameBuffer(unsigned int id) {
			this->id = id;
		}

		FrameBuffer(unsigned int id, unsigned int textureAttachment, ScreenQuad screenQuad) {
			this->id = id;
			this->textureAttachment = textureAttachment;
			this->screenQuad = screenQuad;
		}
	};

}

namespace PhysX {

	struct RigidBody {
		Vec2 position;
		Vec2 direction;
		Vec2 movement;
		float acceleration;
		float vmax;
	};

	struct Geometry {
		const Binding::VertexData vertexData;
		const Binding::IndexData triangulatedIndexData;
		Mat4 transformation;
	};

	struct Triangle {
		Vec2 p1, p2, p3;
	};

}

namespace CustomMath {

	// Source: https://stackoverflow.com/questions/1375882/mathematically-find-max-value-without-conditional-comparison
	static float min(const float a, const float b) {
		return ((a + b) - abs(a - b)) / 2;
	}

	static float max(const float a, const float b) {
		return ((a + b) + abs(a - b)) / 2;
	}

}

namespace Projection {

	static Mat4 getOrthographicProjection(const float width, const float height) {
		return Mat4::ortho(0.0f, width, height, 0.0f, -100.0f, 100.0f);
	}

}