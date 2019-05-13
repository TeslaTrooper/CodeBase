#ifndef STRUCTS
#define STRUCTS

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <AL/al.h>
#include <AL/alc.h>

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
		unsigned int width, height;

		ScreenQuad screenQuad;

		FrameBuffer(int width, int height) : id(0), width(width), height(height) {}

		FrameBuffer(unsigned int id, unsigned int textureAttachment, ScreenQuad screenQuad, int width, int height) :
			id(id), width(width), height(height), textureAttachment(textureAttachment), screenQuad(screenQuad) {}
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
		Vec2 bbox;
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

	enum Format {
		BMP
	};

	struct TextureInfo {
		int width, height;
		const void* parsedData;

		TextureInfo(int width, int height, const void* data) :
			width(width), height(height), parsedData(data) {}

		~TextureInfo() {
			delete[] parsedData;
		}
	};

	struct Color {
		unsigned char r, g, b;

		Color() : Color(0, 0, 0) {}
		Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}
	};

}

namespace File {

	static FILE* open(const char* const file) {
		FILE* f = nullptr;

		errno_t error;
		error = fopen_s(&f, file, "rb");
		if (error != 0) {
			printf("Unable to open file %s \n", file);
		}

		return f;
	}

	static unsigned char* read(const char* const file) noexcept {
		FILE* f = open(file);

		fseek(f, 0, SEEK_END);
		long lSize = ftell(f);
		rewind(f);

		unsigned char* data = new unsigned char[lSize];
		fread(data, lSize, 1, f);
		fclose(f);

		return data;
	}

	static int readBytes(char* buffer, int count, FILE* stream) {
		return (int) fread(buffer, sizeof(char), count, stream);
	}

	static int readBytes(unsigned char* buffer, int count, FILE* stream) {
		return (int) fread(buffer, sizeof(unsigned char), count, stream);
	}

}

namespace Sound {

	enum Format {
		MONO8 = AL_FORMAT_MONO8,		MONO16 = AL_FORMAT_MONO16,
		STEREO8 = AL_FORMAT_STEREO8,	STEREO16 = AL_FORMAT_STEREO16,
		UNSUPPORTED = 0
	};

	struct WaveData {
		const Format format;
		unsigned char* const data;
		const int chunkSize;
		const int rate;

		WaveData(Format format, unsigned char* data, int chunkSize, int rate) :
			format(format), data(data), chunkSize(chunkSize), rate(rate) {}
	};

}

namespace UserInput {

	enum Key {
		KEY_SPACE = GLFW_KEY_SPACE,	KEY_UP = GLFW_KEY_UP,		KEY_RIGHT = GLFW_KEY_RIGHT,
		KEY_DOWN = GLFW_KEY_DOWN,	KEY_LEFT = GLFW_KEY_LEFT,	KEY_SHIFT = GLFW_KEY_LEFT_SHIFT
	};

}

#endif STRUCTS