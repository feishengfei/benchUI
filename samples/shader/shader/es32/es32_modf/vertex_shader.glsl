#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;

in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	float i1;
	vec2 i2;
	vec3 i3;
	vec4 i4;
	float y1 = modf(vPosition.x, i1) + i1;
	vec2 y2 = modf(vec2(1.0, vPosition.x), i2) + i2;
	vec3 y3 = modf(vec3(1.0, 1.0, vPosition.x), i3) + i3;
	vec4 y4 = modf(vec4(1.0, 1.0, 1.0, vPosition.x), i4) + i4;
	float y_average = 0.25 * (y1 + y2.y + y3.z + y4.w);

	gl_Position = vec4(vPosition.x / 2.0, (y_average - vPosition.x) / 2.0, vPosition.z, 1.0); 
	vfColor = vColor;
	gl_PointSize = 8.0;

}
