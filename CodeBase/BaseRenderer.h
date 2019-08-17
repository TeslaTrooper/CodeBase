#pragma once

#include <GL/glew.h>
#include <vector>
#include <map>

#include "structs.h"
#include "Mat4.h"
#include "BufferConfigurator.h"

#define CLEAR_COLOR 0.0f

using namespace Binding;

class BaseRenderer {

	BufferConfigurator bufferConfigurator;
	map<int, FrameBuffer> framebuffers;

	struct BufferTriple {
		unsigned int vao, ebo, vbo;

		BufferTriple(unsigned int vao, unsigned int ebo, unsigned int vbo) : vao(vao), ebo(ebo), vbo(vbo) {}
	};

	vector<BufferTriple> buffers;

public:

	virtual ~BaseRenderer();

	/*
		Creates a new framebuffer and changes the current render target to it.
		@param	x is the x position of the framebuffer relative to default framebuffer
		@param	y is the y position of the framebuffer relative to default framebuffer
		@param	winWidth is the width of the buffer.
		@param	winheight is the height of the buffer.
		@return the index of the framebuffer for later binding.
	*/
	int createFrameBuffer(int x, int y, int winWidth, int winHeight);


	/*
		Use this method to bind to a different framebuffer.
		@param	identifier is used to identify the framebuffer. This value should be
				one of the returned values of createFrameBuffer(...).
	*/
	void bindFrameBuffer(int identifier) const;


	/*
		In order to render vertices on a render target, the vertex information
		has to be configured first.
		@param		bindable represents all necessary information for
					configuring the vertex data.
		@param		drawMode defines the OpenGL drawMode for this bindable.
		@returns	the configuration data, which can be used later for
					rendering this bindable.

	*/
	RenderData configure(const Bindable& bindable, const int drawMode);


	/*
		Is the main render loop, which calls beginDraw, render
		and endDraw implicitly.
		@param	dt is the time since last frame.
	*/
	void update(const float dt) const;


	/*
		Initializes rendering on a specific framebuffer. This method has to
		be called before rendering internalLogic objects.
		@param	framebufferID specifies the render target. Set this to 0
				to use defualt framebuffer as render target.
	*/
	virtual void beginDraw() const;


	/*
		This method draws data on the specified render target.
		@param	data combines all information, which is necessary
				in order to draw polygons.
	*/
	virtual void draw(const RenderData& data) const;


	/*
		After the rendering procedure, this method can be used
		to finalize rendering (unbind all buffers).
	*/
	virtual void endDraw() const;


	/*
		This method gets called implicitly during window creation.
		Use this method to initialize your custom renderer, instead of constructor.
		@param	is the width for default framebuffer, which was created during window
				initialization.
		@param	is the height for default framebuffer, which was created during window
				initialization.
	*/
	virtual void setup(int defaultFramebufferWidth, int defaultFramebufferHeight);


	/*
		This method gets called implicitly by update
		and should be used to render all internalLogic objects
		by invoking the draw function for each object.
	*/
	virtual void render() const = 0;

};