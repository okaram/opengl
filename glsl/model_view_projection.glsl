#version 120 

attribute  vec4 vPosition;
attribute  vec4 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() 
{
    gl_Position = projection*model*view*vPosition/vPosition.w;
    gl_FrontColor = vColor;
    gl_BackColor = vColor;
} 
