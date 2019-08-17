#pragma once

#include <map>

#include "structs.h"

using namespace UserInput;

class KeyCallbackHandler {

	static map<int, bool> keys;

public:

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static bool isKeyPressed(Key key);
	static void release(Key key);

};