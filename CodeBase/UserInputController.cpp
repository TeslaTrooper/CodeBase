#include "UserInputController.h"

map<int, bool> UserInputController::keys;

void UserInputController::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS)
		keys[key] = true;

	if (action == GLFW_RELEASE)
		keys[key] = false;
}

bool UserInputController::isKeyPressed(Key key) {
	if (keys.find(key) != keys.end())
		return keys.at(key);

	return false;
}

void UserInputController::release(Key key) {
	keys[key] = false;
}