#ifndef BUFFER_CONFIGURATOR
#define BUFFER_CONFIGURATOR

#include <GL/glew.h>
#include <stdio.h>

#include "Vec2.h"
#include "structs.h"

using namespace Binding;

class BufferConfigurator {

public:

	struct ScreenQuad {
		unsigned int vao, vbo;
	};

	struct FrameBuffer {
		unsigned int id;
		unsigned int textureAttachment;
		ScreenQuad screenQuad;
	};

	struct BufferData {
		unsigned int vao;
		unsigned int ebo;
		unsigned int vbo;
		int indexCount;
	};

	BufferData configure(const Bindable& bindable) const;
	FrameBuffer createFrameBuffer(const Vec2 winSize) const;

private:

	ScreenQuad configureScreenQuad() const;
	int getOffset(const int currAttribIndex, const AttributeData attributeData) const;

};

#endif BUFFER_CONFIGURATOR