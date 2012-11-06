#version 120
attribute  vec2 vPosition;

void main() 
{
	
    gl_Position = vec4(vPosition.x, vPosition.y, 0.0,1.0);
   // gl_FrontColor=vec4(0.0,0.0,0.0,1.0);
    gl_FrontColor = vec4(abs(vPosition.x), abs(vPosition.y),abs((vPosition.x+vPosition.y)/2),1.0);
//   gl_BackColor = vec4(abs(vPosition.x), abs(vPosition.y),abs((vPosition.x+vPosition.y)/2),1.0);

} 
