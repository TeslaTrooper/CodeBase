#ifndef BUFFER_CONFIGURATOR
#define BUFFER_CONFIGURATOR

#include <GL/glew.h>
#include <stdio.h>

#include "Vec2.h"
#include "structs.h"

using namespace Binding;

class BufferConfigurator {

	ScreenQuad configureScreenQuad() const;
	int getOffset(const int currAttribIndex, const AttributeData& attributeData) const;

public:

	RenderData configure(const Bindable& bindable, const int drawMode) const;
	FrameBuffer createFrameBuffer(const Vec2& winSize) const;

};

#endif BUFFER_CONFIGURATOR