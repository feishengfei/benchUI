#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

float det22(mat2x2 mat22){
	float det = mat22[0][0] * mat22[1][1] - mat22[1][0] * mat22[0][1];
	return det;
}

float det33(mat3x3 mat33){
	mat2x2 mat_00 = mat2x2(
							mat33[1][1], mat33[1][2],
							mat33[2][1], mat33[2][2]
						  );
	mat2x2 mat_01 = mat2x2(
							mat33[1][0], mat33[1][2],
							mat33[2][0], mat33[2][2]
						  );
	mat2x2 mat_02 = mat2x2(
							mat33[1][0], mat33[1][1],
							mat33[2][0], mat33[2][1]
						  );									
	float det = mat33[0][0] * det22(mat_00) - mat33[0][1] * det22(mat_01) + mat33[0][2] * det22(mat_02);
	return det;	
}

float det44(mat4x4 mat44){
	mat3x3 mat_00 = mat3x3(
							mat44[1][1], mat44[1][2], mat44[1][3],
							mat44[2][1], mat44[2][2], mat44[2][3],
							mat44[3][1], mat44[3][2], mat44[3][3]
						  );
	mat3x3 mat_01 = mat3x3(
							mat44[1][0], mat44[1][2], mat44[1][3],
							mat44[2][0], mat44[2][2], mat44[2][3],
							mat44[3][0], mat44[3][2], mat44[3][3]
						  );
	mat3x3 mat_02 = mat3x3(
							mat44[1][0], mat44[1][1], mat44[1][3],
							mat44[2][0], mat44[2][1], mat44[2][3],
							mat44[3][0], mat44[3][1], mat44[3][3]
						  );
	mat3x3 mat_03 = mat3x3(
							mat44[1][0], mat44[1][1], mat44[1][2], 
							mat44[2][0], mat44[2][1], mat44[2][2], 
							mat44[3][0], mat44[3][1], mat44[3][2]
						  );							  									
	float det = mat44[0][0] * det33(mat_00) - mat44[0][1] * det33(mat_01) + mat44[0][2] * det33(mat_02) - mat44[0][3] * det33(mat_03);
	return det;	
}



void main()
{
	mat2x2 m22 = mat2x2(
						1.0, vPosition.x,
						3.0, vPosition.x
				);

	mat3x3 m33 = mat3x3(
						1.0, vPosition.x, 3.0,
						4.0, vPosition.x, 6.0,
						1.0, 1.0, 1.0
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
	sum = 	abs(det22(m22) - determinant(m22)) +
			abs(det33(m33) - determinant(m33)) +
			abs(det44(m44) - determinant(m44));
//	average = sum / 3.0;
	gl_Position = vec4(vPosition.x / 1.0, sum / 1.0, vPosition.z, 1.0);
	vfColor = vColor;
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
