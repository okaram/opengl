#include "../Angel/Angel.h"

#include <iostream>
#include <vector>
using namespace std;
typedef Angel::vec3  point;

vector<point> points { {0,0.5,-0.5}, {-0.5,-0.5,0}, {0.5,-0.5,0}};

vector<point> points2 { {-1,0.5,-0.5}, {-0.5,-0.5,0}, {0.5,-0.5,0}};

int width=400,height=400;

GLuint vaos[2];
    GLuint program, program2;
// OpenGL initialization
void
init()
{
    // Load shaders and use the resulting shader program
    program = InitShader( "lights_vshader.glsl", "green_fshader.glsl" );
	program2=InitShader( "lights_vshader.glsl", "red_fshader.glsl" );
    
    glUseProgram( program );
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );


	
    // Create a vertex array object
    glGenVertexArrays( 2, vaos );
    
    glBindVertexArray( vaos[0] );
    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point)*points.size() ,
		  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point)*points.size(), &points[0] );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

	cout << "vaos[0]=" << vaos[0] <<" buf=" << buffer << endl;
    glBindVertexArray( vaos[1] );
    glGenBuffers( 1, &buffer );
	cout << "vaos[1]=" << vaos[1] <<" buf=" << buffer << endl;
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point)*points2.size() ,
		  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point)*points2.size(), &points2[0] );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT, GL_FALSE, 0,
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
}

void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glUseProgram(program);
    glBindVertexArray( vaos[0] );
	glDrawArrays( GL_TRIANGLES, 0, points.size() );
	
	glUseProgram(program2);
	glBindVertexArray( vaos[1] );
	glDrawArrays( GL_TRIANGLES, 0, points2.size() );
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

