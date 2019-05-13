#include "BaseOpenGLWindow.h"

BaseOpenGLWindow::BaseOpenGLWindow(InternalLogic* const internalLogic, BaseOpenGLRenderer* const renderer, int x, int y, int w, int h, const char* const title) : 
	internalLogic(internalLogic), renderer(renderer) {
	initGLFW();
	initWindow(x, y, w, h, title);
	initViewport();

	renderer->setup(w, h);
}

BaseOpenGLWindow::~BaseOpenGLWindow() {
	delete internalLogic;
	delete renderer;
	glfwDestroyWindow(window);
}

void BaseOpenGLWindow::initGLFW() const {
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

	glewInit();
}

void BaseOpenGLWindow::initViewport() const {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
}

void BaseOpenGLWindow::registerKeyListener() const {
	glfwSetKeyCallback(window, UserInputController::key_callback);
}

void BaseOpenGLWindow::run() {
	GLfloat start = 0;
	GLfloat dt = 0;

	while (!shouldClose()) {
		start = (GLfloat) glfwGetTime();

		glfwPollEvents();

		if (dt < (GLfloat) (1000.f / FRAME_RATE) / 1000.f && dt > 0) {
			dt += (GLfloat) glfwGetTime() - start;
			continue;
		}

		loop((float) dt);
		glfwSwapBuffers(window);

		dt = (GLfloat) glfwGetTime() - start;
	}

	glfwTerminate();
}

void BaseOpenGLWindow::loop(float dt) {
	internalLogic->update(dt);
	renderer->update(dt);
	checkInput(dt);
}