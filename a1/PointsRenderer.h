#ifndef _POINTS_RENDERER_H_
#define _POINTS_RENDERER_H_

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>

template <typename T>
class Point2 {
public:
	T x,y;
	Point2(const T&px, const T&py):x(px),y(py) {}
	void render(void) {
		glVertex3f(x,y,0);
	}
};


class PointsRenderer {
private:
	static float interpolate(float from, float to, int f, int t, int x);
	static std::vector<Point2<GLfloat> > points ;
	static float red, green, blue;
	static int ptSize;

public:
	static int width, height;
	static void changeViewport(int w, int h);
	static float interpolateX(int x) {return interpolate(-1,1,0,width,x);}
	static float interpolateY(int y) {return interpolate(1,-1,0,height,y);}
	static void render(void);
	static void mouseHandler(int button, int state, int x, int y);
	static void keyboardHandler(unsigned char key, int x, int y);
	static void setupGlut();
};

#endif