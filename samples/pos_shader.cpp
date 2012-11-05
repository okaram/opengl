#include "../Angel/Angel.h"

#include <iostream>
#include <vector>
using namespace std;
typedef Angel::vec2  point2;
typedef Angel::vec3  color3;

vector<point2> points { {0.0f,0.0f}, {1.0f,1.0f}, {0.0f,1.0f}};
vector<color3> colors { {1,0,0}, {0.7,0.2,0.2}, {0.5,0.3,0.3}};

int width=400,height=400;


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
    glBufferData( GL_ARRAY_BUFFER, sizeof(point2)*points.size() + sizeof(color3)*colors.size(),
		  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point2)*points.size(), &points[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point2)*points.size(), sizeof(color3)*colors.size(), &colors[0] );

    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "simple_vshader.glsl", "simple_fshader.glsl" );
    glUseProgram( program );

    // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    cout << "vPosition = " << vPosition << endl;
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 2, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

    GLuint vColor = glGetAttribLocation( program, "vColor" ); 
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 3, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(sizeof(point2)*points.size()) );
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
	glDrawArrays( GL_TRIANGLES, 0, points.size() );
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

