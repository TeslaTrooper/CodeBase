#include "BaseController.h"

BaseController::BaseController(InternalLogic* const internalLogic, BaseRenderer* const renderer, int x, int y, int w, int h, const char* const title) :
	internalLogic(internalLogic), renderer(renderer) {
	initGLFW();
	initWindow(x, y, w, h, title);
	initViewport();

	renderer->setup(w, h);
}

BaseController::~BaseController() {
	delete internalLogic;
	delete renderer;
	glfwDestroyWindow(window);
}

void BaseController::initGLFW() const {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void BaseController::initWindow(int x, int y, int w, int h, const char* const title) {
	window = glfwCreateWindow(w, h, title, nullptr, nullptr);

	glfwSetWindowPos(window, x, y);
	glfwMakeContextCurrent(window);

	glewInit();
}

void BaseController::initViewport() const {
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);
}

void BaseController::registerKeyListener() const {
	glfwSetKeyCallback(window, KeyCallbackHandler::key_callback);
}

void BaseController::run() {
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

void BaseController::loop(float dt) {
	internalLogic->update(dt);
	renderer->update(dt);
	checkInput(dt);
}