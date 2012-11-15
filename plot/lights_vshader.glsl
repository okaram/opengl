#version 120
attribute  vec3 vPosition;

void main() 
{
    gl_Position = vec4(vPosition.xyz,1.0);
    gl_FrontColor = vec4(1.0,0.0,0.0,1.0);
    gl_BackColor = vec4(1.0,0.0,0.0,1.0);
} 
