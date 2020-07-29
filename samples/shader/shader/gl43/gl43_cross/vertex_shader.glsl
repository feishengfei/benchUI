#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	float angle = radians(vPosition.x);
	vec3 y3 = cross(vec3(cos(angle), sin(angle), 0.0), vec3(0.0, 0.0, 1.0));
	float y_average = y3.x;

	gl_Position = vec4(vPosition.x / 180.0, y_average / 1.0, vPosition.z, 1.0); 
	vfColor = vColor;
	gl_PointSize = 8.0;
}
