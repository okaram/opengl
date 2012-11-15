atttribute  vec4 vPosition;
atttribute  vec4 vColor;
varying vec4 color;

void main() 
{
  gl_Position = vPosition;
  color = vColor;
} 
