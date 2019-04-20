#ifndef USER_INPUT_CONTROLLER
#define USER_INPUT_CONTROLLER

#include <map>

#include "structs.h"

using namespace UserInput;

class UserInputController {

	static map<int, bool> keys;

public:

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	static bool isKeyPressed(Key key);
	static void release(Key key);

};

#endif USER_INPUT_CONTROLLER
