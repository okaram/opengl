#include "../Angel/Angel.h"

#include <iostream>
#include <vector>
using namespace std;
typedef Angel::vec3  point;

vector<point> points { 
	{0,0.5,-0.5}, {-0.5,-0.5,0}, {0.5,-0.5,0}, 
	{-1,-1,0}, {0,0,0}, {1,-1,0},
};
vector<point> normals {
	{0,0.5,-0.5}, {-0.5,-0.5,0}, {0.5,-0.5,0},
	{0,1,0}, {0,1,0}, {0,1,0},
};
//vector<point> points2 { {-1,0.5,-0.5}, {-0.5,-0.5,0}, {0.5,-0.5,0}};

int width=400,height=400;

GLuint vaos[1];
    GLuint program, program2;
// OpenGL initialization
void
init()
{
    // Load shaders and use the resulting shader program
    program = InitShader( "lights_vshader.glsl", "simple_fshader.glsl" );
    
    glUseProgram( program );
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    GLuint vNormal = glGetAttribLocation( program, "vNormal" );
	
    // Create a vertex array object
    glGenVertexArrays( 1, vaos );
    
    glBindVertexArray( vaos[0] );
    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(point)*points.size() + sizeof(point)*normals.size() ,
		  NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point)*points.size(), &points[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point)*points.size(),sizeof(point)*normals.size(), &points[0] );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );
    glEnableVertexAttribArray( vNormal );
    glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0,
			   BUFFER_OFFSET(sizeof(point)*points.size()) );




/*

    model = glGetUniformLocation( program, "model" );
    view = glGetUniformLocation( program, "view" );
    projection = glGetUniformLocation( program, "projection" );
*/    
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 ); 
    glPointSize(5);
}

float lightColor[3]={0,0,0};


void timerFunc(int value)
{
	cout << "timing " << value << endl;
	lightColor[2]+=0.2;
	glutPostRedisplay();
	glutTimerFunc(1000,timerFunc, value+1);
}

void display(void)
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glUseProgram(program);
    
    GLuint vColor = glGetUniformLocation( program, "vColor" );
	glUniform4f(vColor, 1.0, 0.5,0.0,1.0);

    GLuint lColor = glGetUniformLocation( program, "lColor" );
	glUniform4f(lColor, lightColor[0], lightColor[1],lightColor[2],1.0);

	GLuint lPosition=glGetUniformLocation(program, "lPosition");
	glUniform3f(lPosition, 1.0, 1.0,1.0);
	
	GLuint vNormal=glGetUniformLocation(program, "vNormal");
	glUniform3f(vNormal, 0.0, 1.0,1.0);

    glBindVertexArray( vaos[0] );	
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
	glutTimerFunc(1000,timerFunc, 0);

    glutMainLoop();
    return 0;
}

