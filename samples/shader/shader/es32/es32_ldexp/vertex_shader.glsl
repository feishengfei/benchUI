#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	int e1;
	float x1 = frexp(vPosition.x, e1);
	float y1 = ldexp(x1, e1);

	ivec2 e2;
	vec2 x2 = frexp(vec2(1.0, vPosition.x), e2);
	vec2 y2 = ldexp(x2, e2);

	ivec3 e3;
	vec3 x3 = frexp(vec3(1.0, 1.0, vPosition.x), e3);
	vec3 y3 = ldexp(x3, e3);

	ivec4 e4;
	vec4 x4 = frexp(vec4(1.0, 1.0, 1.0, vPosition.x), e4);
	vec4 y4 = ldexp(x4, e4);

	float y_average = 0.25 * (y1 + y2.y + y3.z + y4.w);

	gl_Position = vec4(vPosition.x / 3.0, y_average - vPosition.x, vPosition.z, 1.0); 
	vfColor = vColor;
	gl_PointSize = 8.0;
}
