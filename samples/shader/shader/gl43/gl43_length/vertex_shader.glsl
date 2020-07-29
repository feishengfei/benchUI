#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	float y1 = length(vPosition.x) - sqrt((vPosition.x)*(vPosition.x));
	float y2 = length(vec2(1.0, vPosition.x)) - sqrt(1.0*1.0 + (vPosition.x)*(vPosition.x));
	float y3 = length(vec3(1.0, 1.0, vPosition.x)) - sqrt(1.0*1.0 + 1.0*1.0 + (vPosition.x)*(vPosition.x));
	float y4 = length(vec4(1.0, 1.0, 1.0, vPosition.x)) - sqrt(1.0*1.0 + 1.0*1.0 + 1.0*1.0 + (vPosition.x)*(vPosition.x));
	float y_average = 0.25 * (y1 + y2 + y3 + y4);

	gl_Position = vec4(vPosition.x / 2.0, y_average / 2.0, vPosition.z, 1.0); 
	vfColor = vColor;
	gl_PointSize = 8.0;
}
