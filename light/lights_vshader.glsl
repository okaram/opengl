#version 120
attribute  vec3 vPosition;
attribute vec3 vNormal;
uniform vec4 vColor;
uniform vec3 lPosition; // position of the light
uniform vec4 lColor; // intensity of the light (per r,g,b)

void main() 
{
	
    gl_Position = vec4(vPosition.x, vPosition.y, vPosition.y,1.0);
    float ratio=dot(vNormal,normalize(lPosition));
    gl_FrontColor = clamp(vColor+lColor*ratio,0,1);
//    gl_BackColor = vColor+lColor*ratio;
    
    //gl_FrontColor=vColor;
    //gl_BackColor = vColor;
} 
