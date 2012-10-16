#include "Assignment1.h"
#include <iostream>

extern int winId;
// C++ is not friendly sometimes ... :)
float Assignment1::red=1;
float Assignment1::green=0;
float Assignment1::blue=0;
int Assignment1::ptSize=3;

int Assignment1::width=800;
int Assignment1::height=600;

int Assignment1::display_mode=GL_POINTS;

std::vector<Point2<GLfloat> > Assignment1::points ;
void Assignment1::changeViewport(int w, int h){
	width=w;
	height=h;
	glViewport(0, 0, w, h);
}


float Assignment1::interpolate(float from, float to, int f, int t, int x)
{
	float frac=(x-f)/(float)(t-f);
	return from+(frac*(to-from));
}

void Assignment1::render(void)
{
	std::cout << "rendering function ..." << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(ptSize);
	glLineWidth(ptSize); // I know; bad variable name :)

	glColor3f(red,green,blue);
	glBegin(display_mode);
		for(unsigned i=0; i<points.size();++i) {
			points[i].render();
			std::cout << "rendering ..." << points[i].x << ',' << points[i].y << std::endl; 
		}
	glEnd();
	glutSwapBuffers();
}
void Assignment1::mouseHandler(int button, int state, int x, int y)
{
	float x1=interpolate(-1,1,0,width,x);
	float y1=interpolate(1,-1,0,height,y);
	std::cout << "b="<< button << " s=" << state << " x=" << x << " y="<<y << " x1=" << x1 << " y1=" << y1 <<std::endl;

	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		points.push_back(Point2<GLfloat>(x1,y1));
		glutPostRedisplay();
	}
}

void Assignment1::keyboardHandler(unsigned char key, int x, int y)
{
	std::cout << "kbd key=" << key << " x=" << x << " y=" << y << std::endl;
	switch(tolower(key)) {
		case 'r':
			red=1; green=0; blue=0;
			break;
		case 'g':
			red=0; green=1; blue=0;
			break;
		case 'b':
			red=0; green=0; blue=1;
			break;
		case '+':
			++ptSize;
			break;
		case '-':
			--ptSize;
			break;
		case 'q':
			exit(0); // or, see below
			glutDestroyWindow(winId);
		
			break;
		case 'p':
			display_mode=GL_POINTS;
			break;
		case 'l':
			display_mode=GL_LINE_STRIP;
			break;
		case 't':
			display_mode=GL_TRIANGLE_STRIP;
			break;

		case 'f':
			glutFullScreen();
			return;
				
	}
	glutPostRedisplay();

}

void Assignment1::setupGlut()
{
	glutDisplayFunc(render);
	glutMouseFunc(mouseHandler);
	glutKeyboardFunc(keyboardHandler);
	glutReshapeFunc(changeViewport);

}
