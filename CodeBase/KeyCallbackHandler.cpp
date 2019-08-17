#include "KeyCallbackHandler.h"

map<int, bool> KeyCallbackHandler::keys;

void KeyCallbackHandler::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode) {
	if (action == GLFW_PRESS)
		keys[key] = true;

	if (action == GLFW_RELEASE)
		keys[key] = false;
}

bool KeyCallbackHandler::isKeyPressed(Key key) {
	if (keys.find(key) != keys.end())
		return keys.at(key);

	return false;
}

void KeyCallbackHandler::release(Key key) {
	keys[key] = false;
}