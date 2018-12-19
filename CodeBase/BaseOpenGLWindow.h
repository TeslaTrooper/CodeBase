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

	virtual void loop(float dt) = 0;

};