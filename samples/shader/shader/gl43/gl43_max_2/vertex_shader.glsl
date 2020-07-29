#version   ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	float y1 = max(vPosition.x, 0.5);
	vec2 y2 = max(vec2(1.0, vPosition.x), vec2(1.0, 0.5));
	vec3 y3 = max(vec3(1.0, 1.0, vPosition.x), vec3(1.0, 1.0, 0.5));
	vec4 y4 = max(vec4(1.0, 1.0, 1.0, vPosition.x), vec4(1.0, 1.0, 1.0, 0.5));
	float y_average = 0.25 * (y1 + y2.y + y3.z + y4.w);


	

	float y1_1 = max(0.4, 0.5) - 0.5;
	float y1_2 = max(0.6, 0.5) - 0.6;	
	vec2 y2_1 = max(vec2(1.0, 0.4), vec2(1.0, 0.5)) - vec2(1.0, 0.5);
	vec2 y2_2 = max(vec2(1.0, 0.6), vec2(1.0, 0.5)) - vec2(1.0, 0.6);
	vec3 y3_1 = max(vec3(1.0, 1.0, 0.4), vec3(1.0, 1.0, 0.5)) - vec3(1.0, 1.0, 0.5);
	vec3 y3_2 = max(vec3(1.0, 1.0, 0.6), vec3(1.0, 1.0, 0.5)) - vec3(1.0, 1.0, 0.6);
	vec4 y4_1 = max(vec4(1.0, 1.0, 1.0, 0.4), vec4(1.0, 1.0, 1.0, 0.5)) - vec4(1.0, 1.0, 1.0, 0.5);
	vec4 y4_2 = max(vec4(1.0, 1.0, 1.0, 0.6), vec4(1.0, 1.0, 1.0, 0.5)) - vec4(1.0, 1.0, 1.0, 0.6);

	float y_average_1 = y1_1 + y1_2 + y2_1.y + y2_2.y + y3_1.z + y3_2.z + y4_1.w + y4_2.w;

	float y1_1_s = max(0.4, 0.5) - 0.5;
	float y1_2_s = max(0.6, 0.5) - 0.6;	
	vec2 y2_1_s = max(vec2(1.0, 0.4), 0.5) - vec2(1.0, 0.5);
	vec2 y2_2_s = max(vec2(1.0, 0.6), 0.5) - vec2(1.0, 0.6);
	vec3 y3_1_s = max(vec3(1.0, 1.0, 0.4), 0.5) - vec3(1.0, 1.0, 0.5);
	vec3 y3_2_s = max(vec3(1.0, 1.0, 0.6), 0.5) - vec3(1.0, 1.0, 0.6);
	vec4 y4_1_s = max(vec4(1.0, 1.0, 1.0, 0.4), 0.5) - vec4(1.0, 1.0, 1.0, 0.5);
	vec4 y4_2_s = max(vec4(1.0, 1.0, 1.0, 0.6), 0.5) - vec4(1.0, 1.0, 1.0, 0.6);

	float y_average_1_s = y1_1 + y1_2 + y2_1.y + y2_2.y + y3_1.z + y3_2.z + y4_1.w + y4_2.w;



	int y1_1_I = max(4, 5) - 5;
	int y1_2_I = max(6, 5) - 6;	
	ivec2 y2_1_I = max(ivec2(10, 4), ivec2(10, 5)) - ivec2(10, 5);
	ivec2 y2_2_I = max(ivec2(10, 6), ivec2(10, 5)) - ivec2(10, 6);
	ivec3 y3_1_I = max(ivec3(10, 10, 4), ivec3(10, 10, 5)) - ivec3(10, 10, 5);
	ivec3 y3_2_I = max(ivec3(10, 10, 6), ivec3(10, 10, 5)) - ivec3(10, 10, 6);
	ivec4 y4_1_I = max(ivec4(10, 10, 10, 4), ivec4(10, 10, 10, 5)) - ivec4(10, 10, 10, 5);
	ivec4 y4_2_I = max(ivec4(10, 10, 10, 6), ivec4(10, 10, 10, 5)) - ivec4(10, 10, 10, 6);

	int y_average_1_I = y1_1_I + y1_2_I + y2_1_I.y + y2_2_I.y + y3_1_I.z + y3_2_I.z + y4_1_I.w + y4_2_I.w;

	int y1_1_s_I = max(4, 5) - 5;
	int y1_2_s_I = max(6, 5) - 6;	
	ivec2 y2_1_s_I = max(ivec2(10, 4), 5) - ivec2(10, 5);
	ivec2 y2_2_s_I = max(ivec2(10, 6), 5) - ivec2(10,6);
	ivec3 y3_1_s_I = max(ivec3(10, 10, 4), 5) - ivec3(10, 10, 5);
	ivec3 y3_2_s_I = max(ivec3(10, 10, 6), 5) - ivec3(10, 10, 6);
	ivec4 y4_1_s_I = max(ivec4(10, 10, 10, 4), 5) - ivec4(10, 10, 10, 5);
	ivec4 y4_2_s_I = max(ivec4(10, 10, 10, 6), 5) - ivec4(10, 10, 10, 6);

	int y_average_1_s_I = y1_1_s_I + y1_2_s_I + y2_1_s_I.y + y2_2_s_I.y + y3_1_s_I.z + y3_2_s_I.z + y4_1_s_I.w + y4_2_s_I.w;




	uint y1_1_U = max(4u, 5u) - 5u;
	uint y1_2_U = max(6u, 5u) - 6u;	
	uvec2 y2_1_U = max(uvec2(10u, 4u), uvec2(10u, 5u)) - uvec2(10u, 5u);
	uvec2 y2_2_U = max(uvec2(10u, 6u), uvec2(10u, 5u)) - uvec2(10u, 6u);
	uvec3 y3_1_U = max(uvec3(10u, 10u, 4u), uvec3(10u, 10u, 5u)) - uvec3(10u, 10u, 5u);
	uvec3 y3_2_U = max(uvec3(10u, 10u, 6u), uvec3(10u, 10u, 5u)) - uvec3(10u, 10u, 6u);
	uvec4 y4_1_U = max(uvec4(10u, 10u, 10u, 4u), uvec4(10u, 10u, 10u, 5u)) - uvec4(10u, 10u, 10u, 5u);
	uvec4 y4_2_U = max(uvec4(10u, 10u, 10u, 6u), uvec4(10u, 10u, 10u, 5u)) - uvec4(10u, 10u, 10u, 6u);

	uint y_average_1_U = y1_1_U + y1_2_U + y2_1_U.y + y2_2_U.y + y3_1_U.z + y3_2_U.z + y4_1_U.w + y4_2_U.w;

	uint y1_1_s_U = max(4u, 5u) - 5u;
	uint y1_2_s_U = max(6u, 5u) - 6u;	
	uvec2 y2_1_s_U = max(uvec2(10u, 4u), 5u) - uvec2(10u, 5u);
	uvec2 y2_2_s_U = max(uvec2(10u, 6u), 5u) - uvec2(10u,6u);
	uvec3 y3_1_s_U = max(uvec3(10u, 10u, 4u), 5u) - uvec3(10u, 10u, 5u);
	uvec3 y3_2_s_U = max(uvec3(10u, 10u, 6u), 5u) - uvec3(10u, 10u, 6u);
	uvec4 y4_1_s_U = max(uvec4(10u, 10u, 10u, 4u), 5u) - uvec4(10u, 10u, 10u, 5u);
	uvec4 y4_2_s_U = max(uvec4(10u, 10u, 10u, 6u), 5u) - uvec4(10u, 10u, 10u, 6u);

	uint y_average_1_s_U = y1_1_s_U + y1_2_s_U + y2_1_s_U.y + y2_2_s_U.y + y3_1_s_U.z + y3_2_s_U.z + y4_1_s_U.w + y4_2_s_U.w;


	

	gl_Position = vec4(vPosition.x / 2.0, (y_average + y_average_1 + y_average_1_s + float(y_average_1_I + y_average_1_s_I) +  float(y_average_1_U + y_average_1_s_U)) / 2.0, vPosition.z, 1.0); 
	vfColor = vColor;
	gl_PointSize = 8.0;
}
