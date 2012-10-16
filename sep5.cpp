#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

GLint vertexID;
GLint fragID;
GLuint shader;


// You shouldn't have to call this function (it's called from the functions
// that make shaders); it is a helper function to determine if a shader compiled correctly.
int compiledStatus(GLint shaderID){
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
		printf ("%s\n", msgBuffer);
		delete (msgBuffer);
		return false;
	}
}

// This function takes in the source code for a vertex shader,
// compiles it, and returns the ID (number) of the shader. It returns
// -1 if the shader didn't compile
GLint makeVertexShader (const char* shaderSource) {
	GLint vShaderID = glCreateShader(GL_VERTEX_SHADER);
	cout << "createshader" << endl;
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
GLuint makeFragmentShader (const char* shaderSource) {
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
bool linkedStatus(GLint programID){
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
GLint makeShaderProgram (GLint vertexShaderID, GLint fragmentShaderID) {
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

// Any time the window is resized, this function gets called.  It's setup to the 
// "glutReshapeFunc" in main.
void changeViewport(int w, int h){
	glViewport(0, 0, w, h);
}


double r=1, g=0,b=0;
// Here is the function that gets called each time the window needs to be redrawn.
// It is the "paint" method for our program, and is set up from the glutDisplayFunc in main
void render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(3);
//	glEnable (GL_CULL_FACE);
	glCullFace (GL_BACK);
	glEnable (GL_DEPTH_TEST);

	glEnable (GL_BLEND);
	#define PI 3.14159265
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(r,g,b);
		glVertex3f(0,0,0);
		for(int deg=0; deg<=720; deg+=120) {
			glVertex3f(cos(deg*PI/360),sin(deg*PI/360),0);
		}


	glEnd();
	glutSwapBuffers();
}


void keyboardHandler(unsigned char key, int x, int y)
{
	cout << "kbd got " << key << " x=" << x << " y=" << y << endl;
	switch(key) {
	case 'g':
		g=1;
		r=0;
		b=0;
		glutPostRedisplay();
		break;
	}
}

void inc_blue(int value) {
	cout << "inc blue " << endl;
	b+=0.1;
	if(value<8) {
		glutTimerFunc(300,inc_blue,value+1);
		glutPostRedisplay();
	}
}

int main (int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);

	cout << "gi " << endl;
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	// Set the window size
	glutInitWindowSize(800, 600);
	// Create the window with the title "Triangle"
	glutCreateWindow("Triangle");
	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(changeViewport);
	glutDisplayFunc(render);
	glutKeyboardFunc(keyboardHandler);
	glutTimerFunc(100,inc_blue,0);
	cout << "all gi " << endl;

	// Very important!  This initializes the entry points in the OpenGL driver so we can 
	// call all the functions in the API.
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	const char* vertexProg = "#version 120\n\
					   void main () {\n\
							gl_Position = gl_Vertex;\
							gl_FrontColor=gl_Color;\
					   }\n";

	const char* fragmentProg="#version 120\n\
					   void main () {\n\
					   gl_FragColor = gl_Color;\n\
					   }\n";


	vertexID = makeVertexShader (vertexProg);
	fragID = makeFragmentShader (fragmentProg);
	shader = makeShaderProgram(vertexID, fragID);

	glUseProgram (shader);

	cout << "Vertex ID is " << vertexID << endl;
	cout << "Fragment ID is " << fragID << endl;
	cout << "Shader program ID is " << shader << endl;

	// Start up a loop that runs in the background (you never see it).
	glutMainLoop();
	return 0;
}
