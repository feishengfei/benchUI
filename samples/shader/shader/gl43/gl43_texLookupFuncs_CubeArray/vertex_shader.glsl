#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;

uniform highp samplerCubeArray texUnit0;
uniform highp isamplerCubeArray texUnit1;
uniform highp usamplerCubeArray texUnit2;

uniform highp samplerCubeArrayShadow texUnit3;

uniform highp samplerBuffer texUnit4;
uniform highp isamplerBuffer texUnit5;
uniform highp usamplerBuffer texUnit6;

out vec4 vfColor;


void main()
{

	bool results[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);



	ivec3 search0 = textureSize(texUnit0, 1);
	results[0] = (search0 == ivec3(2, 2, 2));

	ivec3 search1 = textureSize(texUnit1, 1);
	results[1] = (search1 == ivec3(2, 2, 2));

	ivec3 search2 = textureSize(texUnit2, 1);
	results[2] = (search2 == ivec3(2, 2, 2));

	ivec3 search3 = textureSize(texUnit3, 1);
	results[3] = (search3 == ivec3(2, 2, 2));

	int search4 = textureSize(texUnit4);
	results[4] = (search4 == 16);

	int search5 = textureSize(texUnit5);
	results[5] = (search5 == 16);

	int search6 = textureSize(texUnit6);
	results[6] = (search6 == 16);

	vec4 search7 = texture(texUnit0, vec4(0.125 - 0.5, 0.125 - 0.5, -0.5, 0.0));
	results[7] = (search7.y == 15.1 + 16.0 * 5.0);

	ivec4 search8 = texture(texUnit1, vec4(0.125 - 0.5, 0.125 - 0.5, -0.5, 0.0));
	results[8] = (search8.x == 1500 + 1600 * 5);

	uvec4 search9 = texture(texUnit2, vec4(0.125 - 0.5, 0.125 - 0.5, -0.5, 0.0));
	results[9] = (search9.x == 1500u + 1600u * 5u);

	vec4 search10 = texelFetch(texUnit4, 1);
	results[10] = (search10.x == 1.0);

	ivec4 search11 = texelFetch(texUnit5, 1);
	results[11] = (search11.x == 100);

	uvec4 search12 = texelFetch(texUnit6, 1);
	results[12] = (search12.x == 100u);

	float search13 = texture(texUnit3, vec4(0.125 - 0.5, 0.125 - 0.5, -0.5, 0.0), (15.0 + 16.0 * 5.0) * 0.01 - 0.001);
	results[13] = (search13 == 1.0);

	float search14 = texture(texUnit3, vec4(0.125 - 0.5, 0.125 - 0.5, -0.5, 0.0), (15.0 + 16.0 * 5.0) * 0.01 + 0.001);
	results[14] = (search14 == 0.0);

	vec4 search15 = textureGather(texUnit3, vec4(0.625 - 0.5, 0.875 - 0.5, -0.5, 0.0), (1.0 + 16.0 * 5.0) * 0.01 + 0.001);
	results[15] = (search15 == vec4(1.0, 1.0, 1.0, 0.0));

	vec4 search16 = textureLod(texUnit0, vec4(0.25 - 0.5, 0.25 - 0.5, -0.5, 0.0), 1.0);
	results[16] = (search16.y == 3.11 + 4.0 * 5.0);

	ivec4 search17 = textureLod(texUnit1, vec4(0.25 - 0.5, 0.25 - 0.5, -0.5, 0.0), 1.0);
	results[17] = (search17.y == 311 + 400 * 5);

	uvec4 search18 = textureLod(texUnit2, vec4(0.25 - 0.5, 0.25 - 0.5, -0.5, 0.0), 1.0);
	results[18] = (search18.y == 311u + 400u * 5u);

	vec4 search19 = textureGrad(texUnit0, vec4(0.125 - 0.5, 0.125 - 0.5, -0.5, 0.0), vec3(0.01, 0.02, 0.01), vec3(0.01, 0.02, 0.01));
	results[19] = (search19.y == 15.1 + 16.0 * 5.0);	

	ivec4 search20 = textureGrad(texUnit1, vec4(0.125 - 0.5, 0.125 - 0.5, -0.5, 0.0), vec3(0.01, 0.02, 0.01), vec3(0.01, 0.02, 0.01));
	results[20] = (search20.x == 1500 + 1600 * 5);	

	uvec4 search21 = textureGrad(texUnit2, vec4(0.125 - 0.5, 0.125 - 0.5, -0.5, 0.0), vec3(0.01, 0.02, 0.01), vec3(0.01, 0.02, 0.01));
	results[21] = (search21.x == 1500u + 1600u * 5u);

	vec4 search22 = textureGather(texUnit0, vec4(0.625 - 0.5, 0.875 - 0.5, -0.5, 0.0));
	results[22] = (search22 == vec4(5.0 + 16.0 * 5.0, 6.0 + 16.0 * 5.0, 2.0 + 16.0 * 5.0, 1.0 + 16.0 * 5.0));	

	ivec4 search23 = textureGather(texUnit1, vec4(0.625 - 0.5, 0.875 - 0.5, -0.5, 0.0));
	results[23] = (search23 == ivec4(500 + 1600 * 5, 600 + 1600 * 5, 200 + 1600 * 5, 100 + 1600 * 5));	

	uvec4 search24 = textureGather(texUnit2, vec4(0.625 - 0.5, 0.875 - 0.5, -0.5, 0.0));
	results[24] = (search24 == uvec4(500u + 1600u * 5u, 600u + 1600u * 5u, 200u + 1600u * 5u, 100u + 1600u * 5u));	











	



	











	gl_Position = vec4(vPosition.x / 16.0, float(results[gl_VertexID]) / 2.0, vPosition.z, 1.0);
//	gl_Position = vec4(vPosition.x / 16.0, float(search9.x == 6.0), vPosition.z, 1.0);

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
