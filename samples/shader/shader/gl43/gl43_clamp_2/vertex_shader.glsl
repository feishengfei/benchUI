#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	float y1 = clamp(vPosition.x, -1.0, 1.0);
	vec2 y2 = clamp(vec2(1.0, vPosition.x), -1.0, 1.0);
	vec3 y3 = clamp(vec3(1.0, 1.0, vPosition.x), -1.0, 1.0);
	vec4 y4 = clamp(vec4(1.0, 1.0, 1.0, vPosition.x), -1.0, 1.0);

	float y_average = 0.25 * (y1 + y2.y + y3.z + y4.w);


	int y1_1 = clamp(-15, -10, 10) - (-10);
	int y1_2 = clamp(7, -10, 10) - (7);
	int y1_3 = clamp(15, -10, 10) - (10);

	ivec2 y2_1 = clamp(ivec2(1, -15), ivec2(1, -10), ivec2(1, 10)) - ivec2(-10);
	ivec2 y2_2 = clamp(ivec2(1, 7), ivec2(1, -10), ivec2(1, 10)) - ivec2(7);
	ivec2 y2_3 = clamp(ivec2(1, 15), ivec2(1, -10), ivec2(1, 10)) - ivec2(10);

	ivec3 y3_1 = clamp(ivec3(1, 1, -15), ivec3(1, 1, -10), ivec3(1, 11, 10)) - ivec3(-10);
	ivec3 y3_2 = clamp(ivec3(1, 1, 7), ivec3(1, 11, -10), ivec3(1, 11, 10)) - ivec3(7);
	ivec3 y3_3 = clamp(ivec3(1, 1, 15), ivec3(1, 11, -10), ivec3(1, 11, 10)) - ivec3(10);

	ivec4 y4_1 = clamp(ivec4(1, 1, 1, -15), ivec4(1, 1, 1, -10), ivec4(1, 1, 11, 10)) - ivec4(-10);
	ivec4 y4_2 = clamp(ivec4(1, 1, 1, 7), ivec4(1, 1, 11, -10), ivec4(1, 1, 11, 10)) - ivec4(7);
	ivec4 y4_3 = clamp(ivec4(1, 1, 1, 15), ivec4(1, 1, 11, -10), ivec4(1, 1, 11, 10)) - ivec4(10);


	int y_average_2 = y1_1 + y1_2 + y1_3 + y2_1.y + y2_2.y + y2_3.y + y3_1.z + y3_2.z + y3_3.z + y4_1.w + y4_2.w + y4_3.w;

	int y1_1_s = clamp(-15, -10, 10) - (-10);
	int y1_2_s = clamp(7, -10, 10) - (7);
	int y1_3_s = clamp(15, -10, 10) - (10);

	ivec2 y2_1_s = clamp(ivec2(1, -15), -10, 10) - ivec2(-10);
	ivec2 y2_2_s = clamp(ivec2(1, 7), -10, 10) - ivec2(7);
	ivec2 y2_3_s = clamp(ivec2(1, 15), -10, 10) - ivec2(10);

	ivec3 y3_1_s = clamp(ivec3(1, 1, -15), -10, 10) - ivec3(-10);
	ivec3 y3_2_s = clamp(ivec3(1, 1, 7), -10, 10) - ivec3(7);
	ivec3 y3_3_s = clamp(ivec3(1, 1, 15), -10, 10) - ivec3(10);

	ivec4 y4_1_s = clamp(ivec4(1, 1, 1, -15), -10, 10) - ivec4(-10);
	ivec4 y4_2_s = clamp(ivec4(1, 1, 1, 7), -10, 10) - ivec4(7);
	ivec4 y4_3_s = clamp(ivec4(1, 1, 1, 15), -10, 10) - ivec4(10);

	int y_average_2_s = y1_1_s + y1_2_s + y1_3_s + y2_1_s.y + y2_2_s.y + y2_3_s.y + y3_1_s.z + y3_2_s.z + y3_3_s.z + y4_1_s.w + y4_2_s.w + y4_3_s.w;



	uint y1_1_u = clamp(2u, 6u, 10u) - (6u);
	uint y1_2_u = clamp(12u, 6u, 10u) - (10u);
	uint y1_3_u = clamp(8u, 6u, 10u) - (8u);

	uvec2 y2_1_u = clamp(uvec2(1u, 2u), uvec2(1u, 6u), uvec2(1u, 10u)) - uvec2(6u);
	uvec2 y2_2_u = clamp(uvec2(1u, 12u), uvec2(1u, 6u), uvec2(1u, 10u)) - uvec2(10u);
	uvec2 y2_3_u = clamp(uvec2(1u, 8u), uvec2(1u, 6u), uvec2(1u, 10u)) - uvec2(8u);

	uvec3 y3_1_u = clamp(uvec3(1u, 1u, 2u), uvec3(1u, 1u, 6u), uvec3(1u, 11u, 10u)) - uvec3(6u);
	uvec3 y3_2_u = clamp(uvec3(1u, 1u, 12u), uvec3(1u, 11u, 6u), uvec3(1u, 11u, 10u)) - uvec3(10u);
	uvec3 y3_3_u = clamp(uvec3(1u, 1u, 8u), uvec3(1u, 11u, 6u), uvec3(1u, 11u, 10u)) - uvec3(8u);

	uvec4 y4_1_u = clamp(uvec4(1u, 1u, 1u, 2u), uvec4(1u, 1u, 1u, 6u), uvec4(1u, 1u, 11u, 10u)) - uvec4(6u);
	uvec4 y4_2_u = clamp(uvec4(1u, 1u, 1u, 12u), uvec4(1u, 1u, 11u, 6u), uvec4(1u, 1u, 11u, 10u)) - uvec4(10u);
	uvec4 y4_3_u = clamp(uvec4(1u, 1u, 1u, 8u), uvec4(1u, 1u, 11u, 6u), uvec4(1u, 1u, 11u, 10u)) - uvec4(8u);


	uint y_average_2_u = y1_1_u + y1_2_u+ y1_3_u+ y2_1_u.y + y2_2_u.y + y2_3_u.y + y3_1_u.z + y3_2_u.z + y3_3_u.z + y4_1_u.w + y4_2_u.w + y4_3_u.w;



	uint y1_1_s_u = clamp(2u, 6u, 10u) - (6u);
	uint y1_2_s_u = clamp(12u, 6u, 10u) - (10u);
	uint y1_3_s_u = clamp(8u, 6u, 10u) - (8u);

	uvec2 y2_1_s_u = clamp(uvec2(1u, 2u), 6u, 10u) - uvec2(6u);
	uvec2 y2_2_s_u = clamp(uvec2(1u, 12u), 6u, 10u) - uvec2(10u);
	uvec2 y2_3_s_u = clamp(uvec2(1u, 8u), 6u, 10u) - uvec2(8u);

	uvec3 y3_1_s_u = clamp(uvec3(1u, 1u, 2u), 6u, 10u) - uvec3(6u);
	uvec3 y3_2_s_u = clamp(uvec3(1u, 1u, 12u), 6u, 10u) - uvec3(10u);
	uvec3 y3_3_s_u = clamp(uvec3(1u, 1u, 8u), 6u, 10u) - uvec3(8u);

	uvec4 y4_1_s_u = clamp(uvec4(1u, 1u, 1u, 2u), 6u, 10u) - uvec4(6u);
	uvec4 y4_2_s_u = clamp(uvec4(1u, 1u, 1u, 12u), 6u, 10u) - uvec4(10u);
	uvec4 y4_3_s_u = clamp(uvec4(1u, 1u, 1u, 8u), 6u, 10u) - uvec4(8u);

	uint y_average_2_s_u = y1_1_s_u + y1_2_s_u + y1_3_s_u + y2_1_s_u.y + y2_2_s_u.y + y2_3_s_u.y + y3_1_s_u.z + y3_2_s_u.z + y3_3_s_u.z + y4_1_s_u.w + y4_2_s_u.w + y4_3_s_u.w;

	
	


	gl_Position = vec4(vPosition.x / 2.0, (y_average + float(y_average_2 + y_average_2_s) + float(y_average_2_u + y_average_2_s_u)) / 2.0, vPosition.z, 1.0); 
	vfColor = vColor;


	gl_PointSize = 8.0;
}
