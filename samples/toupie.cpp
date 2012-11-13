#include "../Angel/Angel.h"
#include <iostream>
#include <vector>
using namespace std;
typedef Angel::vec3  color3;
typedef Angel::vec3  point3;


int width=400,height=400;

struct triangle {
	point3 vertices[3];
	triangle(point3 p1, point3 p2, point3 p3)
	{
		vertices[0]=p1;
		vertices[1]=p2;
		vertices[2]=p3;
	}
};
const double PI=3.1415927;
float deg2rad(float deg) { return deg*PI/180.0;}
point3 circle_point(double radius, double deg, double z)
{
	return point3(cos(deg2rad(deg)),sin(deg2rad(deg)), z);
}

vector<triangle> make_sphere()
{
	vector<triangle> vertices;
	const unsigned NUM_STEPS =10;
	for(unsigned i=0; i<NUM_STEPS; ++i) {
		int degrees=i*360/NUM_STEPS;
		vertices.push_back(  triangle(point3(0,0,-0.5), circle_point(1,degrees,0),circle_point(1,degrees+360/NUM_STEPS,0)));
		vertices.push_back(  triangle(point3(0,0,+0.5), circle_point(1,degrees,0),circle_point(1,degrees+360/NUM_STEPS,0)));
	}
	return vertices;
}


vector<triangle> triangles =make_sphere();

// OpenGL initialization
void
init()
{
    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(triangle)*triangles.size() ,
		  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(triangle)*triangles.size(), &triangles[0] );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "simplest_v3_vshader.glsl", "red_fshader.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    cout << "vPosition = " << vPosition << endl;
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

/*
    model = glGetUniformLocation( program, "model" );
    view = glGetUniformLocation( program, "view" );
    projection = glGetUniformLocation( program, "projection" );
*/    
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
}

void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glDrawArrays( GL_TRIANGLES, 0, 3*triangles.size() );
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

