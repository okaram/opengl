#include "PointsRenderer.h"
#include <iostream>

extern int winId;
// C++ is not friendly sometimes ... :)
float PointsRenderer::red=1;
float PointsRenderer::green=0;
float PointsRenderer::blue=0;
int PointsRenderer::ptSize=3;

int PointsRenderer::width=800;
int PointsRenderer::height=600;

std::vector<Point2<GLfloat> > PointsRenderer::points ;
void PointsRenderer::changeViewport(int w, int h){
	std::cout << "chg vp w=" << w << " h=" << h << std::endl;
	width=w;
	height=h;
	glViewport(0, 0, w, h);
}


float PointsRenderer::interpolate(float from, float to, int f, int t, int x)
{
	float frac=(x-f)/(float)(t-f);
	return from+(frac*(to-from));
}

void PointsRenderer::render(void)
{
	std::cout << "rendering function ..." << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(ptSize);
	glColor3f(red,green,blue);
	glBegin(GL_POINTS);
		for(unsigned i=0; i<points.size();++i) {
			points[i].render();
			std::cout << "rendering ..." << points[i].x << ',' << points[i].y << std::endl; 
		}
	glEnd();
	glutSwapBuffers();
}
void PointsRenderer::mouseHandler(int button, int state, int x, int y)
{
	float x1=interpolate(-1,1,0,width,x);
	float y1=interpolate(1,-1,0,height,y);
	std::cout << "b="<< button << " s=" << state << " x=" << x << " y="<<y << " x1=" << x1 << " y1=" << y1 <<std::endl;

	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
		points.push_back(Point2<GLfloat>(x1,y1));
		glutPostRedisplay();
	}
}

void PointsRenderer::keyboardHandler(unsigned char key, int x, int y)
{
	std::cout << "kbd key=" << key << " x=" << x << " y=" << y << std::endl;
	switch(key) {
		case 'r':
			red=1; green=0; blue=0;
			glutPostRedisplay();
			break;
		case 'g':
			red=0; green=1; blue=0;
			glutPostRedisplay();
			break;
		case 'b':
			red=0; green=0; blue=1;
			glutPostRedisplay();
			break;
		case '+':
			++ptSize;
			glutPostRedisplay();
			break;
		case '-':
			--ptSize;
			glutPostRedisplay();
			break;
		case 'q':
		case 'Q':
			exit(0); // or, see below
			glutDestroyWindow(winId);
			glutPostRedisplay();
			break;
		case 'f':
		case 'F':
			glutFullScreen();
		
	}
}

void PointsRenderer::setupGlut()
{
	glutDisplayFunc(render);
	glutMouseFunc(mouseHandler);
	glutKeyboardFunc(keyboardHandler);
	glutReshapeFunc(changeViewport);

}