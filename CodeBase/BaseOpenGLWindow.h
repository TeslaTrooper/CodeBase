#pragma once

#define GLEW_STATIC
#define OPENGL_VERSION 3

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "structs.h"
#include "Mat4.h"

class BaseOpenGLWindow {

	GLFWwindow* window;
	int frameRate;

	void initOpenGL();
	void initWindow(int x, int y, int w, int h, const char* const title);
	void initViewport();

	int shouldClose() const { return glfwWindowShouldClose(window); };

public:
	BaseOpenGLWindow(int x, int y, int w, int h, const char* const title);
	~BaseOpenGLWindow();

	void registerKeyCallback(GLFWkeyfun cbFunc);

	/*
		Calling this method will start the main loop, which runs
		until the user closes this window.
	*/
	void run();

	/*
		This method is embedded inside the main loop
		and gets called every frame. It can be used
		to specify the main operations of the game.

		@param dt	specifies the amount of time
					since last frame.
	*/
	virtual void loop(float dt) = 0;

};