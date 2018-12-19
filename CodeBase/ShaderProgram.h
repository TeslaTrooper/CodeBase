#ifndef SHADER_PROGRAM
#define SHADER_PROGRAM

#include <GL/glew.h>
#include <iostream>

/*
Diese Klasse stellt zwei Shader bereit und erlaubt es, aus diesen Shadern
ein fertiges Shader Program zu erzeugen.
*/
class ShaderProgram {

	void compileShader(const GLuint shader, const GLchar* shaderSource) const;

	GLuint createShader(const GLenum shaderType, const GLchar* shaderSource) const;

	char* readShaderFile(char const * const file) const;

public:
	ShaderProgram();
	~ShaderProgram();

	/*
	Erzeugt aus den zwei Shadern ein fertiges Shader Program.
	@return Gibt die von OpenGL erzeugte ID zu diesem Program zurück.
	*/
	GLuint createShaderProgram(const char* vertexShaderFile, const char* fragmentShaderFile) const;

};

#endif SHADER_PROGRAM