#pragma once

#include "Vec2.h"
#include "Mat4.h"

namespace Binding {

	struct IndexData {
		const int* indices;
		int count;
	};

	struct VertexData {
		const float* vertices;
		int componentCount;
		int count;
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