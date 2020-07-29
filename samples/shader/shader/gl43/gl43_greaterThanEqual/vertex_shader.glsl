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

	vec2 r2 = vec2(1.0, 3.0);
	vec3 r3 = vec3(r2, 2.0);
	vec4 r4 = vec4(r3, 4.0);

	bvec2 v2 = greaterThanEqual(c2, r2);
	bvec3 v3 = greaterThanEqual(c3, r3);
	bvec4 v4 = greaterThanEqual(c4, r4);

	float average_v = (float(v2.y) + float(v3.y) + float(v4.y)) / 3.0;

	ivec2 ic2 = ivec2(1, int(vPosition.x));
	ivec3 ic3 = ivec3(ic2, 2);
	ivec4 ic4 = ivec4(ic3, 4);

	ivec2 ir2 = ivec2(1, 3);
	ivec3 ir3 = ivec3(ir2, 2);
	ivec4 ir4 = ivec4(ir3, 4);

	bvec2 iv2 = greaterThanEqual(ic2, ir2);
	bvec3 iv3 = greaterThanEqual(ic3, ir3);
	bvec4 iv4 = greaterThanEqual(ic4, ir4);

	float average_i = (float(iv2.y) + float(iv3.y) + float(iv4.y)) / 3.0;

	uvec2 uc2 = uvec2(1, uint(abs(vPosition.x)));
	uvec3 uc3 = uvec3(uc2, 2);
	uvec4 uc4 = uvec4(uc3, 4);

	uvec2 ur2 = uvec2(1, 3);
	uvec3 ur3 = uvec3(ur2, 2);
	uvec4 ur4 = uvec4(ur3, 4);

	bvec2 uv2 = greaterThanEqual(uc2, ur2);
	bvec3 uv3 = greaterThanEqual(uc3, ur3);
	bvec4 uv4 = greaterThanEqual(uc4, ur4);

	float average_u = (float(uv2.y) + float(uv3.y) + float(uv4.y)) / 3.0;

	float average = average_v + average_i + average_u;

	gl_Position = vec4(vPosition.x / 10.0, average / 3.0, vPosition.z, 1.0);
	vfColor = vColor;
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
