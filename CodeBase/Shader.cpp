#include "Shader.h"

Shader::Shader(const GLuint shaderProgram) : shaderProgram(shaderProgram) {}

Shader::~Shader() {}

void Shader::setUniformMatrix4(const GLchar* uniform, Mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, uniform), 1, GL_FALSE, Mat4::ptr(value));
}

void Shader::setInteger(const GLchar* uniform, GLint value) const {
	glUniform1i(glGetUniformLocation(this->shaderProgram, uniform), value);
}

void Shader::setVector2(const GLchar* uniform, Vec2 value) const {
	glUniform2f(glGetUniformLocation(this->shaderProgram, uniform), value.x, value.y);
}

void Shader::setUniformMatrix3(const GLchar* uniform, Mat3 value) const {
	glUniformMatrix3fv(glGetUniformLocation(this->shaderProgram, uniform), 1, GL_FALSE, Mat3::ptr(value));
}

void Shader::setColor(const GLchar* uniform, Textures::Color color) const {
	float r = (float) color.r / 255.f;
	float g = (float) color.g / 255.f;
	float b = (float) color.b / 255.f;

	glUniform3f(glGetUniformLocation(this->shaderProgram, uniform), r, g, b);
}

void Shader::use() const {
	glUseProgram(this->shaderProgram);
}