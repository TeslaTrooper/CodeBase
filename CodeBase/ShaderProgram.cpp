#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {}

GLuint ShaderProgram::createShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile) const {
	unsigned char* vertexShaderSource = File::read(vertexShaderFile);
	unsigned char* fragmentShaderSource = File::read(fragmentShaderFile);

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, (GLchar*) vertexShaderSource);
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, (GLchar*) fragmentShaderSource);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		std::cout << "Error loading shader program!";
	}

	return shaderProgram;
}

void ShaderProgram::compileShader(const GLuint shader, const GLchar* shaderSource) const {
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		std::cout << "Error compiling shader! " << shader;
	}
}

GLuint ShaderProgram::createShader(const GLenum shaderType, const GLchar* shaderSource) const {
	GLuint shader = glCreateShader(shaderType);
	compileShader(shader, shaderSource);

	return shader;
}

ShaderProgram::~ShaderProgram() {}