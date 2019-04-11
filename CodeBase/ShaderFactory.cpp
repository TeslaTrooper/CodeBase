#include "ShaderFactory.h"

Shader* ShaderFactory::createShader(const char* vertexShaderFile, const char* fragmentShaderFile) {
	unsigned char* vertexShaderSource = File::read(vertexShaderFile);
	unsigned char* fragmentShaderSource = File::read(fragmentShaderFile);

	GLuint vertexShader = configureShader(GL_VERTEX_SHADER, (GLchar*) vertexShaderSource);
	GLuint fragmentShader = configureShader(GL_FRAGMENT_SHADER, (GLchar*) fragmentShaderSource);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
		std::cout << "Error loading shader program!";

	return new Shader(shaderProgram);
}

void ShaderFactory::compileShader(const GLuint shader, const GLchar* shaderSource) {
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
		std::cout << "Error compiling shader! " << shader;
}

GLuint ShaderFactory::configureShader(const GLenum shaderType, const GLchar* shaderSource) {
	GLuint shader = glCreateShader(shaderType);
	compileShader(shader, shaderSource);

	return shader;
}