#version 120
attribute  vec2 vPosition;


float mandel(float x0, float y0)
{
	float x=0;
	float y=0;
	float iter=0;
	while(x*x+y*y < 4 && iter<30.0) {
		float xtemp=x*x-y*y + x0;
		y=2*x*y + y0;
		x=xtemp;
		iter=iter+1.0;
	}
	return iter;
}

void main() 
{
	
    gl_Position = vec4(vPosition.x, vPosition.y, 0.0,1.0);
    float x=-2.5+(vPosition.x+1.0)*1.75;
    float y=-vPosition.y;
    float m=mandel(x,y)/30.0;
    gl_FrontColor = vec4(m, 1.0-m,m/2.0,1.0);
//   gl_BackColor = vec4(abs(vPosition.x), abs(vPosition.y),abs((vPosition.x+vPosition.y)/2),1.0);

} 
