#version       ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
uniform highp sampler2D texUnit0;
uniform highp isampler2D texUnit1;
uniform highp usampler2D texUnit2;
uniform highp sampler3D texUnit3;
uniform highp isampler3D texUnit4;
uniform highp usampler3D texUnit5;
uniform highp sampler2DArray texUnit6;
uniform highp isampler2DArray texUnit7;
uniform highp usampler2DArray texUnit8;
uniform highp samplerCube texUnit9;
uniform highp isamplerCube texUnit10;
uniform highp usamplerCube texUnit11;
//uniform highp samplerCubeArray texUnit12;

out vec4 vfColor;


void main()
{

	bool results[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);



	vec4 search0 = textureGradOffset(texUnit3, vec3(0.625, 0.375, 0.375), vec3(0.01, 0.02, 0.05), vec3(0.03, 0.04, 0.06), ivec3(1, 0, 0));
	results[0] = (search0.y == (22.10 + 1.0));

	ivec4 search1 = textureGradOffset(texUnit4, vec3(0.625, 0.375, 0.375), vec3(0.01, 0.02, 0.05), vec3(0.03, 0.04, 0.06), ivec3(1, 0, 0));
	results[1] = (search1.y == (2210 + 100));

	uvec4 search2 = textureGradOffset(texUnit5, vec3(0.625, 0.375, 0.375), vec3(0.01, 0.02, 0.05), vec3(0.03, 0.04, 0.06), ivec3(1, 0, 0));
	results[2] = (search2.y == (2210u + 100u));


	vec4 search3 = textureGradOffset(texUnit6, vec3(0.75, 0.75, 1.0), vec2(0.1, 0.2), vec2(0.3, 0.4), ivec2(-1, 0));
	results[3] = (search3.y == (7.11 - 1.0));

	ivec4 search4 = textureGradOffset(texUnit7, vec3(0.75, 0.75, 1.0), vec2(0.1, 0.2), vec2(0.3, 0.4), ivec2(-1, 0));
	results[4] = (search4.y == (711 - 100));

	uvec4 search5 = textureGradOffset(texUnit8, vec3(0.75, 0.75, 1.0), vec2(0.1, 0.2), vec2(0.3, 0.4), ivec2(-1, 0));
	results[5] = (search5.y == (711u - 100u));



	vec4 search6 = textureProjGrad(texUnit0, 2.0 * vec3(0.625, 0.375, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04));
	results[6] = (search6.y == 6.10);

	ivec4 search7 = textureProjGrad(texUnit1, 2.0 * vec3(0.625, 0.375, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04));
	results[7] = (search7.y == 610);

	uvec4 search8 = textureProjGrad(texUnit2, 2.0 * vec3(0.625, 0.375, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04));
	results[8] = (search8.y == 610u);

	vec4 search9 = textureProjGrad(texUnit0, 2.0 * vec4(0.625, 0.375, 1.0, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04));
	results[9] = (search9.y == 6.10);

	ivec4 search10 = textureProjGrad(texUnit1, 2.0 * vec4(0.625, 0.375, 0.5, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04));
	results[10] = (search10.y == 610);

	uvec4 search11 = textureProjGrad(texUnit2, 2.0 * vec4(0.625, 0.375, 0.1, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04));
	results[11] = (search11.y == 610u);

	vec4 search12 = textureProjGrad(texUnit3, 2.0 * vec4(0.625, 0.375, 0.375, 1.0), vec3(0.01, 0.02, 0.05), vec3(0.03, 0.04, 0.06));
	results[12] = (search12.y == 22.10);

	ivec4 search13 = textureProjGrad(texUnit4, 2.0 * vec4(0.625, 0.375, 0.375, 1.0), vec3(0.01, 0.02, 0.05), vec3(0.03, 0.04, 0.06));
	results[13] = (search13.y == 2210);

	uvec4 search14 = textureProjGrad(texUnit5, 2.0 * vec4(0.625, 0.375, 0.375, 1.0), vec3(0.01, 0.02, 0.05), vec3(0.03, 0.04, 0.06));
	results[14] = (search14.y == 2210u);



	vec4 search15 = textureProjGradOffset(texUnit0, 2.0 * vec3(0.625, 0.375, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0));
	results[15] = (search15.y == (6.10 + 1.0));

	ivec4 search16 = textureProjGradOffset(texUnit1, 2.0 * vec3(0.625, 0.375, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0));
	results[16] = (search16.y == (610 + 100));

	uvec4 search17 = textureProjGradOffset(texUnit2, 2.0 * vec3(0.625, 0.375, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0));
	results[17] = (search17.y == (610u +100u));

	vec4 search18 = textureProjGradOffset(texUnit0, 2.0 * vec4(0.625, 0.375, 1.0, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0));
	results[18] = (search18.y == (6.10 + 1.0));

	ivec4 search19 = textureProjGradOffset(texUnit1, 2.0 * vec4(0.625, 0.375, 0.5, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0));
	results[19] = (search19.y == (610 + 100));

	uvec4 search20 = textureProjGradOffset(texUnit2, 2.0 * vec4(0.625, 0.375, 0.1, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0));
	results[20] = (search20.y == (610u + 100u));

	vec4 search21 = textureProjGradOffset(texUnit3, 2.0 * vec4(0.625, 0.375, 0.375, 1.0), vec3(0.01, 0.02, 0.05), vec3(0.03, 0.04, 0.06), ivec3(1, 0, 0));
	results[21] = (search21.y == (22.10 + 1.0));

	ivec4 search22 = textureProjGradOffset(texUnit4, 2.0 * vec4(0.625, 0.375, 0.375, 1.0), vec3(0.01, 0.02, 0.05), vec3(0.03, 0.04, 0.06), ivec3(1, 0, 0));
	results[22] = (search22.y == (2210 + 100));

	uvec4 search23 = textureProjGradOffset(texUnit5, 2.0 * vec4(0.625, 0.375, 0.375, 1.0), vec3(0.01, 0.02, 0.05), vec3(0.03, 0.04, 0.06), ivec3(1, 0, 0));
	results[23] = (search23.y == (2210u +100u));



	vec4 search24 = textureGather(texUnit0, vec2(0.625, 0.375), 0);
	results[24] = (search24 == vec4(10.00, 11.00, 7.00, 6.00));

	ivec4 search25 = textureGather(texUnit1, vec2(0.625, 0.375), 0);
	results[25] = (search25 == ivec4(1000, 1100, 700, 600));

	uvec4 search26 = textureGather(texUnit2, vec2(0.625, 0.375), 0);
	results[26] = (search26 == uvec4(1000u, 1100u, 700u, 600u));

	vec4 search27 = textureGather(texUnit6, vec3(0.625, 0.375, 1.0), 0);
	results[27] = (search27 == vec4(26.00, 27.00, 23.00, 22.00));

	ivec4 search28 = textureGather(texUnit7, vec3(0.625, 0.375, 1.0), 0);
	results[28] = (search28 == ivec4(2600, 2700, 2300, 2200));

	uvec4 search29 = textureGather(texUnit8, vec3(0.625, 0.375, 1.0), 0);
	results[29] = (search29 == uvec4(2600u, 2700u, 2300u, 2200u));












	



	











	gl_Position = vec4(vPosition.x / 16.0, float(results[gl_VertexID]) / 2.0, vPosition.z, 1.0);
//	gl_Position = vec4(vPosition.x / 16.0, float(search24.w == 6.00), vPosition.z, 1.0);

	if(gl_VertexID < 10)
		vfColor = vColor;
	else if(gl_VertexID < 20)
		vfColor = vec4(0.0, 0.0, 1.0, 1.0);
	else
		vfColor = vec4(0.0, 1.0, 0.0, 1.0);


		
	gl_PointSize = 8.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
