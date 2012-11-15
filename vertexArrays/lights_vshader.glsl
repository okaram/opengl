#version 120
attribute  vec3 vPosition;
uniform vec4 vColor;
uniform vec4 lPosition;
uniform vec4 lColor;

void main() 
{
	
    gl_Position = vec4(vPosition.x, vPosition.y, 0.0,1.0);
    gl_FrontColor = vec4(1.0,0.0,0.0,1.0);
    gl_BackColor = vec4(1.0,0.0,0.0,1.0);
} 
