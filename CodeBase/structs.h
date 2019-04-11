#ifndef STRUCTS
#define STRUCTS

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

	enum DrawMode {
		LINES = GL_LINES,
		TRIANGLES = GL_TRIANGLES
	};

}

namespace PhysX {

	struct RigidBody {
		Vec2 position;
		Vec2 direction;
		Vec2 movement;
		float acceleration;
		float vmax;

		RigidBody() : acceleration(0), vmax(0) {}
	};

	enum BodyType {
		STATIC, DYNAMIC, KINEMATIC
	};

	struct BodyDefinition {
		BodyType type;
		Vec2 position;
		Vec2 direction;
		Vec2 movement;
		float acceleration;
		float vmax;

		BodyDefinition(const BodyType& type) : type(type), acceleration(0.f), vmax(0.f) {}
	};

	struct FixtureDefinition {
		Mat4 transformation;
		float friction;

		FixtureDefinition() : friction(0.f) {}
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

namespace Textures {

	enum PixelDataType {
		RGB = GL_RGB,
		RGBA = GL_RGBA
	};

	struct TextureInfo {
		int width, height;
		const void* parsedData;

		~TextureInfo() {
			delete[] parsedData;
		}
	};

}

namespace File {

	static FILE* open(const char* const file) {
		FILE* f = nullptr;

		errno_t error;
		error = fopen_s(&f, file, "r");
		if (error != 0) {
			printf("Unable to open file %s \n", file);
		}

		return f;
	}

	static unsigned char* read(const char* const file) {
		FILE* f = open(file);

		fseek(f, 0, SEEK_END);
		long lSize = ftell(f);
		rewind(f);

		unsigned char* data = new unsigned char[lSize];
		fread(data, lSize, 1, f);
		fclose(f);

		return data;
	}

}

namespace Sound {

	enum Format {
		MONO16, STEREO16
	};

	struct WaveData {
		const Format format;
		void* const data;
		const int chunkSize;
		const int rate;

		WaveData(Format format, void* data, int chunkSize, int rate) :
			format(format), data(data), chunkSize(chunkSize), rate(rate) {}
	};

}

#endif STRUCTS