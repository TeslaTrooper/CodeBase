#pragma once

#include <GL/glew.h>

#include "structs.h"
#include "Mat4.h"
#include "BufferConfigurator.h"

using namespace Binding;

class BaseOpenGLRenderer {

	BufferConfigurator bufferConfigurator;
	FrameBuffer framebuffer;

public:

	struct RenderData {
		unsigned int vao;
		int drawMode, indexCount;
	};

	BaseOpenGLRenderer() : framebuffer(0) {};

	/*
		Creates a new framebuffer and changes the current render target to it.
		@param	winWidth is the width of the window.
		@param	winheight is the height of the window.
	*/
	void createFrameBuffer(const int winWidth, const int winHeight);


	/*
		@returns the currently set render target as a FrameBuffer.
	*/
	FrameBuffer getRenderTarget() const { return framebuffer; };


	/*
		In order to render vertices on a render target, the vertex information
		has to be configured first.
		@param		bindable represents all necessary information for
					configuring the vertex data.
		@returns	the configuration data, which can be used later for
					rendering this bindable.

	*/
	BufferConfigurator::BufferData configure(const Bindable bindable) const;


	/*
		Is the main render loop, which calls beginDraw, render
		and endDraw implicitly.
		@param	dt is the time since last frame.
	*/
	void update(const float dt) const;


	/*
		Initializes rendering on a specific framebuffer. This method has to
		be called before rendering game objects.
		@param	framebufferID specifies the render target. Set this to 0
				to use defualt framebuffer as render target.
	*/
	virtual void beginDraw() const;


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


	/*
		This method gets called implicitly by update
		and should be used to render all game objects
		by invoking the draw function for each object.
	*/
	virtual void render() const = 0;


	/*
		Implement this method to change the current projection.
		@param	projection specifies the new projection matrix.
	*/
	virtual void setProjection(const Mat4 projection) const = 0;

};