#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	float y1 = min(vPosition.x, 0.5);
	vec2 y2 = min(vec2(1.0, vPosition.x), vec2(1.0, 0.5));
	vec3 y3 = min(vec3(1.0, 1.0, vPosition.x), vec3(1.0, 1.0, 0.5));
	vec4 y4 = min(vec4(1.0, 1.0, 1.0, vPosition.x), vec4(1.0, 1.0, 1.0, 0.5));
	float y_average = 0.25 * (y1 + y2.y + y3.z + y4.w);



	float y1_1 = min(0.4, 0.5) - 0.4;
	float y1_2 = min(0.6, 0.5) - 0.5;	
	vec2 y2_1 = min(vec2(1.0, 0.4), vec2(1.0, 0.5)) - vec2(1.0, 0.4);
	vec2 y2_2 = min(vec2(1.0, 0.6), vec2(1.0, 0.5)) - vec2(1.0, 0.5);
	vec3 y3_1 = min(vec3(1.0, 1.0, 0.4), vec3(1.0, 1.0, 0.5)) - vec3(1.0, 1.0, 0.4);
	vec3 y3_2 = min(vec3(1.0, 1.0, 0.6), vec3(1.0, 1.0, 0.5)) - vec3(1.0, 1.0, 0.5);
	vec4 y4_1 = min(vec4(1.0, 1.0, 1.0, 0.4), vec4(1.0, 1.0, 1.0, 0.5)) - vec4(1.0, 1.0, 1.0, 0.4);
	vec4 y4_2 = min(vec4(1.0, 1.0, 1.0, 0.6), vec4(1.0, 1.0, 1.0, 0.5)) - vec4(1.0, 1.0, 1.0, 0.5);

	float y_average_1 = y1_1 + y1_2 + y2_1.y + y2_2.y + y3_1.z + y3_2.z + y4_1.w + y4_2.w;

	float y1_1_s = min(0.4, 0.5) - 0.5;
	float y1_2_s = min(0.6, 0.5) - 0.6;	
	vec2 y2_1_s = min(vec2(1.0, 0.4), 0.5) - vec2(1.0, 0.4);
	vec2 y2_2_s = min(vec2(1.0, 0.6), 0.5) - vec2(1.0, 0.5);
	vec3 y3_1_s = min(vec3(1.0, 1.0, 0.4), 0.5) - vec3(1.0, 1.0, 0.4);
	vec3 y3_2_s = min(vec3(1.0, 1.0, 0.6), 0.5) - vec3(1.0, 1.0, 0.5);
	vec4 y4_1_s = min(vec4(1.0, 1.0, 1.0, 0.4), 0.5) - vec4(1.0, 1.0, 1.0, 0.4);
	vec4 y4_2_s = min(vec4(1.0, 1.0, 1.0, 0.6), 0.5) - vec4(1.0, 1.0, 1.0, 0.5);

	float y_average_1_s = y1_1 + y1_2 + y2_1.y + y2_2.y + y3_1.z + y3_2.z + y4_1.w + y4_2.w;



	int y1_1_I = min(4, 5) - 4;
	int y1_2_I = min(6, 5) - 5;	
	ivec2 y2_1_I = min(ivec2(10, 4), ivec2(10, 5)) - ivec2(10, 4);
	ivec2 y2_2_I = min(ivec2(10, 6), ivec2(10, 5)) - ivec2(10, 5);
	ivec3 y3_1_I = min(ivec3(10, 10, 4), ivec3(10, 10, 5)) - ivec3(10, 10, 4);
	ivec3 y3_2_I = min(ivec3(10, 10, 6), ivec3(10, 10, 5)) - ivec3(10, 10, 5);
	ivec4 y4_1_I = min(ivec4(10, 10, 10, 4), ivec4(10, 10, 10, 5)) - ivec4(10, 10, 10, 4);
	ivec4 y4_2_I = min(ivec4(10, 10, 10, 6), ivec4(10, 10, 10, 5)) - ivec4(10, 10, 10, 5);

	int y_average_1_I = y1_1_I + y1_2_I + y2_1_I.y + y2_2_I.y + y3_1_I.z + y3_2_I.z + y4_1_I.w + y4_2_I.w;

	int y1_1_s_I = min(4, 5) - 4;
	int y1_2_s_I = min(6, 5) - 5;	
	ivec2 y2_1_s_I = min(ivec2(10, 4), 5) - ivec2(10, 4);
	ivec2 y2_2_s_I = min(ivec2(10, 6), 5) - ivec2(10, 5);
	ivec3 y3_1_s_I = min(ivec3(10, 10, 4), 5) - ivec3(10, 10, 4);
	ivec3 y3_2_s_I = min(ivec3(10, 10, 6), 5) - ivec3(10, 10, 5);
	ivec4 y4_1_s_I = min(ivec4(10, 10, 10, 4), 5) - ivec4(10, 10, 10, 4);
	ivec4 y4_2_s_I = min(ivec4(10, 10, 10, 6), 5) - ivec4(10, 10, 10, 5);

	int y_average_1_s_I = y1_1_s_I + y1_2_s_I + y2_1_s_I.y + y2_2_s_I.y + y3_1_s_I.z + y3_2_s_I.z + y4_1_s_I.w + y4_2_s_I.w;



	uint y1_1_U = min(4u, 5u) - 4u;
	uint y1_2_U = min(6u, 5u) - 5u;	
	uvec2 y2_1_U = min(uvec2(10u, 4u), uvec2(10u, 5u)) - uvec2(10u, 4u);
	uvec2 y2_2_U = min(uvec2(10u, 6u), uvec2(10u, 5u)) - uvec2(10u, 5u);
	uvec3 y3_1_U = min(uvec3(10u, 10u, 4u), uvec3(10u, 10u, 5u)) - uvec3(10u, 10u, 4u);
	uvec3 y3_2_U = min(uvec3(10u, 10u, 6u), uvec3(10u, 10u, 5u)) - uvec3(10u, 10u, 5u);
	uvec4 y4_1_U = min(uvec4(10u, 10u, 10u, 4u), uvec4(10u, 10u, 10u, 5u)) - uvec4(10u, 10u, 10u, 4u);
	uvec4 y4_2_U = min(uvec4(10u, 10u, 10u, 6u), uvec4(10u, 10u, 10u, 5u)) - uvec4(10u, 10u, 10u, 5u);

	uint y_average_1_U = y1_1_U + y1_2_U + y2_1_U.y + y2_2_U.y + y3_1_U.z + y3_2_U.z + y4_1_U.w + y4_2_U.w;

	uint y1_1_s_U = min(4u, 5u) - 4u;
	uint y1_2_s_U = min(6u, 5u) - 5u;	
	uvec2 y2_1_s_U = min(uvec2(10u, 4u), 5u) - uvec2(10u, 4u);
	uvec2 y2_2_s_U = min(uvec2(10u, 6u), 5u) - uvec2(10u, 5u);
	uvec3 y3_1_s_U = min(uvec3(10u, 10u, 4u), 5u) - uvec3(10u, 10u, 4u);
	uvec3 y3_2_s_U = min(uvec3(10u, 10u, 6u), 5u) - uvec3(10u, 10u, 5u);
	uvec4 y4_1_s_U = min(uvec4(10u, 10u, 10u, 4u), 5u) - uvec4(10u, 10u, 10u, 4u);
	uvec4 y4_2_s_U = min(uvec4(10u, 10u, 10u, 6u), 5u) - uvec4(10u, 10u, 10u, 5u);

	uint y_average_1_s_U = y1_1_s_U + y1_2_s_U + y2_1_s_U.y + y2_2_s_U.y + y3_1_s_U.z + y3_2_s_U.z + y4_1_s_U.w + y4_2_s_U.w;


	

	gl_Position = vec4(vPosition.x / 2.0, (y_average + y_average_1 + y_average_1_s + float(y_average_1_I + y_average_1_s_I) +  float(y_average_1_U + y_average_1_s_U)) / 2.0, vPosition.z, 1.0); 

	vfColor = vColor;
	gl_PointSize = 8.0;
}
