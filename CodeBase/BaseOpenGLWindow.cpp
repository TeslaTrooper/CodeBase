#include "BaseOpenGLWindow.h"

BaseOpenGLWindow::BaseOpenGLWindow(int x, int y, int w, int h, const char* const title) : frameRate(60) {
	initOpenGL();
	initWindow(x, y, w, h, title);
	initViewport();
}

BaseOpenGLWindow::~BaseOpenGLWindow() {
	glfwDestroyWindow(window);
}

void BaseOpenGLWindow::initOpenGL() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void BaseOpenGLWindow::initWindow(int x, int y, int w, int h, const char* const title) {
	window = glfwCreateWindow(w, h, title, nullptr, nullptr);

	glfwSetWindowPos(window, x, y);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	glGetString(GL_VERSION);
}

void BaseOpenGLWindow::initViewport() {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
}

void BaseOpenGLWindow::registerKeyCallback(GLFWkeyfun cbFunc) {
	glfwSetKeyCallback(window, cbFunc);
}

void BaseOpenGLWindow::run() {
	GLfloat start = 0;
	GLfloat dt = 0;

	while (!shouldClose()) {
		start = (GLfloat) glfwGetTime();

		glfwPollEvents();

		if (dt < (GLfloat) (1000.f / frameRate) / 1000.f && dt > 0) {
			dt += (GLfloat) glfwGetTime() - start;
			continue;
		}

		loop((float) dt);
		glfwSwapBuffers(window);

		dt = (GLfloat) glfwGetTime() - start;
	}

	glfwTerminate();
}