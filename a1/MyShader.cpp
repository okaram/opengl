#include "MyShader.h"
#include <iostream>
#include <cstdio>

// You shouldn't have to call this function (it's called from the functions
// that make shaders); it is a helper function to determine if a shader compiled correctly.
bool MyShader::compiledStatus(GLint shaderID){
	GLint compiled = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compiled);
	if (compiled) {
		return true;
	}
	else {
		GLint logLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);
		char* msgBuffer = new char[logLength];
		glGetShaderInfoLog(shaderID, logLength, NULL, msgBuffer);
		std::cout << msgBuffer << std::endl;
		delete (msgBuffer);
		return false;
	}
}

// This function takes in the source code for a vertex shader,
// compiles it, and returns the ID (number) of the shader. It returns
// -1 if the shader didn't compile
GLint MyShader::makeVertexShader (const char* shaderSource) {
	GLint vShaderID = glCreateShader(GL_VERTEX_SHADER);
	std::cout << "createshader" << std::endl;
	glShaderSource (vShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(vShaderID);
	int compiledCorrectly = compiledStatus(vShaderID);
	if (compiledCorrectly) {
		return vShaderID;
	}
	return -1;
}

// This function takes in the source code for a fragment shader,
// compiles it, and returns the ID (number) of the shader. It returns
// -1 if the shader didn't compile
GLuint MyShader::makeFragmentShader (const char* shaderSource) {
	GLint fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource (fShaderID, 1, (const GLchar**)&shaderSource, NULL);
	glCompileShader(fShaderID);
	int compiledCorrectly = compiledStatus(fShaderID);
	if (compiledCorrectly) {
		return fShaderID;
	}
	return -1;
}

// A helper function that takes in a program ID and returns whether
// or not it linked correctly.  If not, it prints out an error
// message letting you know what the problem was. This will
// be called from makeShaderProgram()
bool MyShader::linkedStatus(GLint programID){
	GLint linked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &linked);
	if (linked) {
		return true;
	}
	else {
		GLint logLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
		char* msgBuffer = new char[logLength];
		glGetProgramInfoLog(programID, logLength, NULL, msgBuffer);
		printf ("%s\n", msgBuffer);
		delete (msgBuffer);
		return false;
	}
}

// A function that takes in the IDs for vertex and fragment shader,
// and returns the ID of a shader program that has been linked.
GLint MyShader::makeShaderProgram (GLint vertexShaderID, GLint fragmentShaderID)
{
	printf ("Linking %d with %d\n", vertexShaderID, fragmentShaderID);
	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram (programID);

	bool linked = linkedStatus (programID);

	if (linked) {
		return programID;
	}
	return -1;
}


const char* passThroughVProg = "#version 120\n\
					   void main () {\n\
							gl_Position = gl_Vertex;\
							gl_FrontColor=gl_Color;\
					   }\n";

const char* passThroughFProg="#version 120\n\
					   void main () {\n\
					   gl_FragColor = gl_Color;\n\
					   }\n";

const char* normalVProg = "#version 120\n\
					   void main () {\n\
						   gl_Position = ftransform();\
							gl_FrontColor=gl_Color;\
					   }\n";

GLint MyShader::makePassThroughShaderProgram() {
	return makeShaderProgram(makeVertexShader (passThroughVProg), makeFragmentShader (passThroughFProg));
}

GLint MyShader::makeNormalShaderProgram() {
	return makeShaderProgram(makeVertexShader (normalVProg), makeFragmentShader (passThroughFProg));
}
