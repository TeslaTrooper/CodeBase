#pragma once

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

