#include "../Angel/Angel.h"

#include <iostream>
#include <vector>
using namespace std;
typedef Angel::vec3  point;

vector<point> points { {0,0.5,-0.5}, {-0.5,-0.5,0}, {0.5,-0.5,0}};


int width=400,height=400;

double foo(double x, double y)
{
	return sin(x)+sin(y);
}
	
double start_u=0.0, end_u=1.0, delta_u=.1;
double start_v=0.0, end_v=1.0, delta_v=.1;

// u, v between 0 and 1 !!
point func(double u, double v)
{
	return point(u,sin(2*(u+v)),v);
}
vector<point> curvySurface()
{
	vector<point> points;
	
	for(double u=start_u; u<end_u; u+=delta_u) {
		for(double v=start_v; v<end_v; v+=delta_v) {
			point p1=func(u,v);
			point p2=func(u,v+delta_v);
			points.push_back(p1);
			points.push_back(p2);
			
			point p3=func(u+delta_u,v);
			points.push_back(p1);
			points.push_back(p3);
		}
	}
	return points;
}

GLuint vaos[1];
    GLuint program, program2;
// OpenGL initialization
void
init()
{
    // Load shaders and use the resulting shader program
    program = InitShader( "v3d_shader.glsl", "../glsl/green_fshader.glsl" );
    points=curvySurface();
    glUseProgram( program );
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );


	
    // Create a vertex array object
    glGenVertexArrays( 1, vaos );
    
    glBindVertexArray( vaos[0] );
    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point)*points.size() ,
		  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point)*points.size(), &points[0] );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );


//    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point2)*points.size(), sizeof(color3)*colors.size(), &colors[0] );


/*
    GLuint vColor = glGetAttribLocation( program, "vColor" ); 
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(sizeof(point2)*points.size()) );

    model = glGetUniformLocation( program, "model" );
    view = glGetUniformLocation( program, "view" );
    projection = glGetUniformLocation( program, "projection" );
*/    
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
    glPointSize(5);
    glLineWidth(3);
    glUseProgram(program);
    
}

void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glUseProgram(program);
    glBindVertexArray( vaos[0] );
	glDrawArrays( GL_LINES, 0, points.size() );
	
	glutSwapBuffers();
}



void
reshape( int width, int height )
{
    glViewport( 0, 0, width, height );
}

//----------------------------------------------------------------------------
int
main( int argc, char **argv )
{

	std::cout << "initing " << std::endl;

    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( width, height );
    glutCreateWindow( "Color Cube" );


    glewInit();

    init();

    glutDisplayFunc( display );
    //glutKeyboardFunc( keyboard );
    glutReshapeFunc( reshape );

    glutMainLoop();
    return 0;
}

