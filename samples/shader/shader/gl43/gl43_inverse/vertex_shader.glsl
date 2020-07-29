#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

float sum_abs_22(mat2x2 mat22){
	float sum = 0.0;
	int i,j;
	for(i = 0; i < 2; i++){
		for(j = 0; j < 2; j++){
			sum += abs(mat22[i][j]);
		}
	}
	return sum;
}

float sum_abs_33(mat3x3 mat33){
	float sum = 0.0;
	int i,j;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			sum += abs(mat33[i][j]);
		}
	}
	return sum;
}

float sum_abs_44(mat4x4 mat44){
	float sum = 0.0;
	int i,j;
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4; j++){
			sum += abs(mat44[i][j]);
		}
	}
	return sum;
}

void main()
{
	mat2x2 m22 = mat2x2(
						1.0, 2.0,
						3.0, vPosition.x
				);				
	mat3x3 m33 = mat3x3(
						1.0, 2.0, 3.0,
						4.0, vPosition.x, 6.0,
						1.0, 1.0, 1.0
				);
	mat4x4 m44 = mat4x4(
						1.0, 2.0, 1.0, 1.0,
						3.0, vPosition.x, 1.0, 1.0,
						5.0, 6.0, 1.0, 1.0,
						7.0, 8.0, 2.0, 1.0
				);

	///	mat4x3 = mat2x3 * mat4x2 
	/// m[2][3]	is the 4th element of the 3th column

	float sum, average;
	sum = 	
			sum_abs_22(m22 * inverse(m22) - mat2(1.0)) + 
			sum_abs_33(m33 * inverse(m33) - mat3(1.0)) +
			sum_abs_44(m44 * inverse(m44) - mat4(1.0));
//	average = sum / 3.0;
	gl_Position = vec4(vPosition.x / 1.0, sum / 1.0, vPosition.z, 1.0);
	vfColor = vColor;
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
