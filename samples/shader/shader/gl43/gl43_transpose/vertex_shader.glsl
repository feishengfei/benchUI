#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	mat2x2 m22 = mat2x2(
						1.0, vPosition.x,
						3.0, vPosition.x
				);
	mat2x3 m23 = mat2x3(
						1.0, vPosition.x, 3.0,
						4.0, vPosition.x, 6.0
				);
	mat2x4 m24 = mat2x4(
						1.0, vPosition.x, 3.0, 1.0,
						4.0, vPosition.x, 6.0, 1.0
				);
	mat3x2 m32 = mat3x2(
						1.0, vPosition.x,
						3.0, vPosition.x,
						1.0, 1.0
				);	
	mat3x3 m33 = mat3x3(
						1.0, vPosition.x, 3.0,
						4.0, vPosition.x, 6.0,
						1.0, 1.0, 1.0
				);
	mat3x4 m34 = mat3x4(
						1.0, vPosition.x, 3.0, 1.0,
						4.0, vPosition.x, 6.0, 1.0,
						1.0, 1.0, 1.0, 1.0
				);	

	mat4x2 m42 = mat4x2(
						1.0, vPosition.x,
						3.0, vPosition.x,
						5.0, 6.0,
						7.0, 8.0
				);
	mat4x3 m43 = mat4x3(
						1.0, vPosition.x, 1.0,
						3.0, vPosition.x, 1.0,
						5.0, 6.0, 1.0,
						7.0, 8.0, 1.0
				);
	mat4x4 m44 = mat4x4(
						1.0, vPosition.x, 1.0, 1.0,
						3.0, vPosition.x, 1.0, 1.0,
						5.0, 6.0, 1.0, 1.0,
						7.0, 8.0, 1.0, 1.0
				);

	///	mat4x3 = mat2x3 * mat4x2 
	/// m[2][3]	is the 4th element of the 3th column

	float sum, average;
	sum = 	(transpose(m22))[1][0] +
			(transpose(m23))[1][0] +
			(transpose(m24))[1][0] +
			(transpose(m32))[1][0] +
			(transpose(m33))[1][0] +
			(transpose(m34))[1][0] +
			(transpose(m42))[1][0] +
			(transpose(m43))[1][0] +
			(transpose(m44))[1][0];
	average = sum / 9.0;

	gl_Position = vec4(vPosition.x / 1.0, (average - vPosition.x) / 1.0, vPosition.z, 1.0);
	vfColor = vColor;
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
