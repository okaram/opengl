#ifndef _SHADERS_H_
#define _SHADERS_H_
#include <GL/glew.h>
#include <GL/freeglut.h>


class MyShader {
public:
	static bool compiledStatus(GLint shaderID);
	static GLint makeVertexShader (const char* shaderSource);
	static GLuint makeFragmentShader (const char* shaderSource);
	static bool linkedStatus(GLint programID);
	static GLint makeShaderProgram (GLint vertexShaderID, GLint fragmentShaderID);
	static GLint makePassThroughShaderProgram();
	static GLint makeNormalShaderProgram();};

#endif