#ifndef SHADER
#define SHADER

#include <GL/glew.h>

#include "structs.h"
#include "Mat3.h"

/*
Die Klasse kapselt das Shader Programm und erlaubt es, uniforms der Shader,
die zu diesem Shader Program gehören, zu manipulieren.
*/
class Shader {

	const GLuint shaderProgram;

public:
	/*
	Erzeugt einen neuen Shader mit einem Shader Programm.
	@param shaderProgram ist das Program, das gekapselt werden soll.
	*/
	Shader(const GLuint shaderProgram);
	~Shader();


	/*
	Setzt zum gegebenen uniform die gegebene Matrix.
	@param uniform ist der Name des uniforms, der im Shader verwendet wird.
	@param value ist die Matrix, die diesem uniform zugeordnet werden soll.
	*/
	void setUniformMatrix4(const GLchar* uniform, Mat4 value) const;


	/*
	Setzt zum gegebenen uniform den gegebenen Integer.
	@param uniform ist der Name des uniforms, der im Shader verwendet wird.
	@param value ist der Integer, der diesem uniform zugeordnet werden soll.
	*/
	void setInteger(const GLchar* uniform, GLint value) const;


	/*
	Setzt zum gegebenen uniform den gegebene Vektor.
	@param uniform ist der Name des uniforms, der im Shader verwendet wird.
	@param value ist der Vektor, der diesem uniform zugeordnet werden soll.
	*/
	void setVector2(const GLchar* uniform, Vec2 value) const;


	/*
	Setzt zum gegebenen uniform die gegebene Matrix.
	@param uniform ist der Name des uniforms, der im Shader verwendet wird.
	@param value ist die Matrix, die diesem uniform zugeordnet werden soll.
	*/
	void setUniformMatrix3(const GLchar* uniform, Mat3 value) const;


	/*
	Verwendet das Program.
	*/
	void use() const;
};

#endif SHADER