#pragma once

#define GLEW_STATIC
#define OPENGL_VERSION 3

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mat4.h"

class BaseOpenGLWindow {

	GLFWwindow* window;
	Mat4 projection;

	int frameRate;

protected:
	void initOpenGL();
	void initWindow(int x, int y, int w, int h, const char* title);
	void initViewport();
	void initProjectionMatrix(int w, int h);

public:
	BaseOpenGLWindow(int x, int y, int w, int h, const char* title);
	~BaseOpenGLWindow();

	void registerKeyCallback(GLFWkeyfun cbFunc);
	void clearWindow() const;
	void run();

	Mat4 getProjectionMatrix() { return projection; };
	int shouldClose() const { return glfwWindowShouldClose(window); };

	/*
		This method is embedded inside the main loop
		and gets called every frame. It can be used
		to specify the main operations of the game.

		@param dt	specifies the amount of time
					since last frame.
	*/
	virtual void loop(float dt) = 0;

};