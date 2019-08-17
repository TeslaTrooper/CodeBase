#pragma once

#define GLEW_STATIC
#define OPENGL_VERSION 3
#define FRAME_RATE 60

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "BaseRenderer.h"
#include "InternalLogic.h"
#include "KeyCallbackHandler.h"

class BaseController {

	BaseRenderer* const renderer;
	InternalLogic* const internalLogic;

	GLFWwindow* window;

	void initWindow(int x, int y, int w, int h, const char* const title);
	void initViewport() const;
	void initGLFW() const;

	int shouldClose() const { return glfwWindowShouldClose(window); };

public:

	BaseController(InternalLogic* const internalLogic, BaseRenderer* const renderer, int x, int y, int w, int h, const char* const title);
	virtual ~BaseController();


	/*
		In order to recognize user inputs via keyboard, use this method
		to add the corresponding listener to the window.
	*/
	void registerKeyListener() const;


	/*
		Calling this method will start the main loop, which runs
		until the user closes this window.
	*/
	void run();


	/*
		This method is embedded inside the main loop
		and gets called every frame. It can be used
		to specify the main operations of the internalLogic.

		@param dt	specifies the amount of time
					since last frame.
	*/
	virtual void loop(float dt);


	/*
		In order to recognize user inputs, implement this method.
		This method gets called implicitly inside main loop.

		@param dt	specifies the amount of time
					since last frame.
	*/
	virtual void checkInput(float dt) = 0;

};