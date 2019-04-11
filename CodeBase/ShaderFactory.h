#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <GL/glew.h>
#include <iostream>

#include "structs.h"
#include "Shader.h"

class ShaderFactory {

	static void compileShader(const GLuint shader, const GLchar* shaderSource);
	static GLuint configureShader(const GLenum shaderType, const GLchar* shaderSource);

public:

	static Shader* createShader(const char* vertexShaderFile, const char* fragmentShaderFile);

};

#endif SHADER_PROGRAM