#version 120 

attribute  vec3 vPosition;
attribute  vec4 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    gl_Position = model*vPosition;
    gl_FrontColor = vColor;
    gl_BackColor = vColor;
} 
