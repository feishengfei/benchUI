#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

float mixBlend(float x, float y, float a)
{
	return (x * (1.0 - a) + y * a) ;
}

void main()
{
	float y1 = mix(-1.0, 1.0, vPosition.x);
	vec2 y2 = mix(vec2(1.0, -1.0), vec2(1.0, 1.0), vec2(1.0, vPosition.x));
	vec3 y3 = mix(vec3(1.0, 1.0, -1.0), vec3(1.0, 1.0, 1.0), vec3(1.0, 1.0, vPosition.x));
	vec4 y4 = mix(vec4(1.0, 1.0, 1.0, -1.0), vec4(1.0, 1.0, 1.0, 1.0), vec4(1.0, 1.0, 1.0, vPosition.x));
	float y_average = 0.25 * (y1 + y2.y + y3.z + y4.w);


	float y1_s = mix(-1.0, 1.0, vPosition.x) - mixBlend(-1.0, 1.0, vPosition.x);
	float y2_s = (mix(vec2(1.0, -1.0), vec2(1.0, 1.0), vPosition.x)).y - mixBlend(-1.0, 1.0, vPosition.x);
	float y3_s = (mix(vec3(1.0, 1.0, -1.0), vec3(1.0, 1.0, 1.0), vPosition.x)).z - mixBlend(-1.0, 1.0, vPosition.x);
	float y4_s = (mix(vec4(1.0, 1.0, 1.0, -1.0), vec4(1.0, 1.0, 1.0, 1.0), vPosition.x)).w - mixBlend(-1.0, 1.0, vPosition.x);
	float y_average_s =y1_s + y2_s + y3_s + y4_s;

	bool y1_1 = (mix(-1.0, 1.0, true) == 1.0) && (mix(-1.0, 1.0, false) == -1.0);
	bool y2_1 = ((mix(vec2(0.0, -1.0), vec2(0.0, 1.0), bvec2(true))).y == 1.0) && ((mix(vec2(0.0, -1.0), vec2(0.0, 1.0), bvec2(false))).y == -1.0);
	bool y3_1 = ((mix(vec3(0.0, 0.0, -1.0), vec3(0.0, 0.0, 1.0), bvec3(true))).z == 1.0) && ((mix(vec3(0.0, 0.0, -1.0), vec3(0.0, 0.0, 1.0), bvec3(false))).z == -1.0);	
	bool y4_1 = ((mix(vec4(0.0, 0.0, 0.0, -1.0), vec4(0.0, 0.0, 0.0, 1.0), bvec4(true))).w == 1.0) && ((mix(vec4(0.0, 0.0, 0.0, -1.0), vec4(0.0, 0.0, 0.0, 1.0), bvec4(false))).w == -1.0);
	float y_average_1 = float(y1_1) + float(y2_1) + float(y3_1) + float(y4_1) - 4.0;


	bool y1_2 = (mix(-1, 1, true) == 1) && (mix(-1, 1, false) == -1);
	bool y2_2 = ((mix(ivec2(0, -1), ivec2(0, 1), bvec2(true))).y == 1) && ((mix(ivec2(0, -1), ivec2(0, 1), bvec2(false))).y == -1);
	bool y3_2 = ((mix(ivec3(0, 0, -1), ivec3(0, 0, 1), bvec3(true))).z == 1) && ((mix(ivec3(0, 0, -1), ivec3(0, 0, 1), bvec3(false))).z == -1);	
	bool y4_2 = ((mix(ivec4(0, 0, 0, -1), ivec4(0, 0, 0, 1), bvec4(true))).w == 1) && ((mix(ivec4(0, 0, 0, -1), ivec4(0, 0, 0, 1), bvec4(false))).w == -1);
	float y_average_2 = float(y1_2) + float(y2_2) + float(y3_2) + float(y4_2) - 4.0;


	bool y1_3 = (mix(0u, 1u, true) == 1u) && (mix(0u, 1u, false) == 0u);
	bool y2_3 = ((mix(uvec2(0u, 0u), uvec2(0u, 1u), bvec2(true))).y == 1u) && ((mix(uvec2(0u, 0u), uvec2(0u, 1u), bvec2(false))).y == 0u);
	bool y3_3 = ((mix(uvec3(0u, 0u, 0u), uvec3(0u, 0u, 1u), bvec3(true))).z == 1u) && ((mix(uvec3(0u, 0u, 0u), uvec3(0u, 0u, 1u), bvec3(false))).z == 0u);	
	bool y4_3 = ((mix(uvec4(0u, 0u, 0u, 0u), uvec4(0u, 0u, 0u, 1u), bvec4(true))).w == 1u) && ((mix(uvec4(0u, 0u, 0u, 0u), uvec4(0u, 0u, 0u, 1u), bvec4(false))).w == 0u);
	float y_average_3 = float(y1_3) + float(y2_3) + float(y3_3) + float(y4_3) - 4.0;


	bool y1_4 = (mix(false, true, true) == true) && (mix(false, true, false) == false);
	bool y2_4 = ((mix(bvec2(false, false), bvec2(false, true), bvec2(true))).y == true) && ((mix(bvec2(false, false), bvec2(false, true), bvec2(false))).y == false);
	bool y3_4 = ((mix(bvec3(false, false, false), bvec3(false, false, true), bvec3(true))).z == true) && ((mix(bvec3(false, false, false), bvec3(false, false, true), bvec3(false))).z == false);	
	bool y4_4 = ((mix(bvec4(false, false, false, false), bvec4(false, false, false, true), bvec4(true))).w == true) && ((mix(bvec4(false, false, false, false), bvec4(false, false, false, true), bvec4(false))).w == false);
	float y_average_4 = float(y1_4) + float(y2_4) + float(y3_4) + float(y4_4) - 4.0;
 

	gl_Position = vec4(vPosition.x / 1.0, (y_average + y_average_s + y_average_1 + y_average_2 + y_average_3 + y_average_4)  / 1.5, vPosition.z, 1.0);
	vfColor = vColor;
	gl_PointSize = 8.0;
}
