#version 120 

attribute  vec2 vPosition;
attribute  vec2 vColor;

uniform mat3 model;
uniform mat3 view;
uniform mat3 projection;

void main() 
{
    gl_Position = model*vPosition;
    gl_FrontColor = vColor;
    gl_BackColor = vColor;
} 
