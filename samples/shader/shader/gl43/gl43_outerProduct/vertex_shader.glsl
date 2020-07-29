#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	vec2 c2 = vec2(1.0, vPosition.x);
	vec3 c3 = vec3(c2, 2.0);
	vec4 c4 = vec4(c3, 4.0);

	vec2 r2 = vec2(1.0, vPosition.x);
	vec3 r3 = vec3(r2, 2.0);
	vec4 r4 = vec4(r3, 4.0);

	mat2x2 m22 = outerProduct(c2, r2);
	mat3x3 m33 = outerProduct(c3, r3);
	mat4x4 m44 = outerProduct(c4, r4);
	mat3x2 m32 = outerProduct(c2, r3);
	mat2x3 m23 = outerProduct(c3, r2);
	mat4x2 m42 = outerProduct(c2, r4);
	mat2x4 m24 = outerProduct(c4, r2);
	mat4x3 m43 = outerProduct(c3, r4);
	mat3x4 m34 = outerProduct(c4, r3);

	///	mat4x3 = mat2x3 * mat4x2 
	/// m[2][3]	is the 4th element of the 3th column

	float average = (m22[1][1] + m33[1][1] + m44[1][1] + m32[1][1] + m23[1][1] + m42[1][1] + m24[1][1] + m34[1][1] + m43[1][1]) / 9.0;

	gl_Position = vec4(vPosition.x / 10.0, average / 100.0, vPosition.z, 1.0);
	vfColor = vColor;
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
