#ifndef BUFFER_CONFIGURATOR
#define BUFFER_CONFIGURATOR

#include <GL/glew.h>
#include <stdio.h>

#include "Vec2.h"
#include "structs.h"

using namespace Binding;

class BufferConfigurator {

	ScreenQuad configureScreenQuad(const Vec2& position, const Vec2& size) const;
	int getOffset(const int currAttribIndex, const AttributeData& attributeData) const;

	float toNDC(float pixel) const {
		return (pixel - .5f) * 2.f;
	}

	Vec2 toNDC(const Vec2& vec) const {
		return Vec2(toNDC(vec.x), toNDC(vec.y));
	}

public:

	RenderData configure(const Bindable& bindable, const int drawMode) const;
	FrameBuffer createFrameBuffer(const Vec2& position, const Vec2& size) const;

};

#endif BUFFER_CONFIGURATOR