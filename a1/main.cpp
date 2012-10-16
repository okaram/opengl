#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include <cstdio>
#include <vector>
#include "MyShader.h"
#include "Assignment1.h"
#include <cmath>


using namespace std;


int winId;


// Any time the window is resized, this function gets called.  It's setup to the 
// "glutReshapeFunc" in main.

void changeViewport(int w, int h){
	glViewport(0, 0, w, h);
}

// Here is the function that gets called each time the window needs to be redrawn.
// It is the "paint" method for our program, and is set up from the glutDisplayFunc in main
void render_blend_depth() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // enable depth testing
	glEnable(GL_BLEND); // enable alpha blending
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // use obvious blending function
	glBegin(GL_TRIANGLES);
		float z=0;
		glColor3f(1,0,0); // alpha is 1, change to see different colors :)
		glVertex3f(-1,1,z);
		glVertex3f(1,1, z);
		glVertex3f(1,-1,z);
		z=-0.1; // change to -1 or any <0 to see blending
		glColor4f(0,1,0,0.5);
		glVertex3f(1,1,z);
		glVertex3f(-1,-1, z);
		glVertex3f(1,-1,z);
	glEnd();
	glutSwapBuffers();
}

float sine(float x) {
	return sin(x*3.14);
}
GLfloat *gen_array(float fromX, float dx, unsigned num_points)
{
	GLfloat* points=new GLfloat[2*num_points];
	for(unsigned i=0; i<=num_points;i+=2) {
		points[i]=fromX+i*dx;
		points[i+1]=sine(points[i]);
	}
	return points;
}

const int num_points=100;
GLfloat* points=gen_array(-1,.02,num_points);

void render_graph() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2,GL_FLOAT,0,points);
	glColor3f(1,0,0);
	glLineWidth(5);
	glDrawArrays(GL_LINE_STRIP,0,num_points/2);
	
	glutSwapBuffers();

}



void render_arrays(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST); // enable depth testing
	//glEnable(GL_BLEND); // enable alpha blending
	//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // use obvious blending function
	GLfloat vertices[]={	-0.8,	0.8,	0.0,
							0.8,	0.8,	0.0,
							0.8,	-0.8,	0.0,
							0.5,	0.5,	0.0,
							-0.9,	0.9,	0.0
						};

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,vertices);
	glPushMatrix();
	glTranslatef(-0.5,0,0);
	glScalef(0.3,1,0);
	glColor3f(1,0,0);
	glPointSize(20);
	glDrawArrays(GL_POINTS,0,sizeof(vertices)/(3*sizeof(vertices[0])));
	
/*	glBegin(GL_POINTS);
		glColor3f(0,0,1); // alpha is 1, change to see different colors :)
		glVertex2f(-1,1);
		glVertex2f(1,1);
		glVertex2f(1,-1);
	glEnd();
	*/
	glutSwapBuffers();
	glPopMatrix();
}

float z=-1;

void keyboardHandler(unsigned char key, int x, int y)
{
	switch(key) {
	case 'z':
		z-=1;
		cout << "z=" << z << endl;
		glutPostRedisplay();
		break;
	case 'Z':
		z+=1;
		cout << "z=" << z << endl;
		glutPostRedisplay();
		break;		
	}
}
void render_3d1(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // enable depth testing
	glEnable(GL_BLEND); // enable alpha blending
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // use obvious blending function

	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio =  800.0 / 600; // or width/height :)
	gluPerspective(45,ratio,1,1000);
	int theta = 45, phi = 45;
	const double radianFactor = 2 * 3.1415926535 / 360; 
	float r = 5.0f;
	float eyeX = r * sin(theta * radianFactor) * cos(phi * radianFactor);
	float eyeY = r * sin(theta * radianFactor) * sin(phi * radianFactor);
	float eyeZ = r * cos(radianFactor * theta);
	cout << "eye " << eyeX << "," << eyeY << "," << eyeZ << endl;
	float centerX = 0, centerY = 0, centerZ = 0;
	float upX = 0, upY = 1.0f, upZ = 0;
	gluLookAt(eyeX, eyeY, eyeZ, 
				  centerX, centerY, centerZ,
				  upX, upY, upZ);
	glMatrixMode(GL_MODELVIEW);
	glColor3f(1,0,0);
	glLoadIdentity();
	glPointSize(3);
	glLineWidth(5);
	//gluPerspective(30,1,0.1,10);
	glBegin(GL_TRIANGLES);
		glColor3f(0,0,1); // alpha is 1, change to see different colors :)
		glVertex3f(-1,1,z);
		glVertex3f(1,1,z);
		glVertex3f(1,-1,z);
	glEnd();
	
	glutSwapBuffers();
	glPopMatrix();
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
	winId=glutCreateWindow("Assignment 1");
	// Bind the two functions (above) to respond when necessary
	//glutReshapeFunc(changeViewport);
	//glutDisplayFunc(render_3d1);
	//glutKeyboardFunc(keyboardHandler);
	Assignment1::setupGlut();
	cout << "all gi " << endl;

	// Very important!  This initializes the entry points in the OpenGL driver so we can 
	// call all the functions in the API.
	
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW error");
		return 1;
	}
	
	glUseProgram ( MyShader::makeNormalShaderProgram()  );

	// Start up a loop that runs in the background (you never see it).
	glutMainLoop();
	return 0;
}
