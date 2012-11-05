#version 120
attribute  vec2 vPosition;
attribute  vec3 vColor;

void main() 
{
	
    gl_Position = vec4(vPosition.x, vPosition.y, 0.0,1.0);
    gl_FrontColor = vec4(vColor.x+vPosition.x, vColor.y+vPosition.y,vColor.z,1.0);
    gl_BackColor = vec4(vColor.r, vColor.g,vColor.b,1.0);
} 
