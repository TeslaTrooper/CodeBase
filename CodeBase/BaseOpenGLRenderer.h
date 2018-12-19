#pragma once

#include <GL/glew.h>
#include <utility>

class BaseOpenGLRenderer {

public:

	struct RenderData {
		unsigned int vao;
		int drawMode, indexCount;
	};

	/*
		Initializes rendering on a specific framebuffer. This method has to
		be called before rendering game objects.
		@param	framebufferID specifies the render target. Set this to 0
				to use defualt framebuffer as render target.
	*/
	virtual void beginDraw(const int framebufferID) const;


	/*
		This method draws data on the specified render target.
		@param	data combines all information, which is necessary
				in order to draw polygons.
	*/
	virtual void draw(const RenderData data) const;


	/*
		After the rendering procedure, this method can be used
		to finalize rendering (unbind all buffers).
	*/
	virtual void endDraw() const;

};