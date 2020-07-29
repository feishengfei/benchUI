#version   ///GLSL Version 3.20

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
	vec4 search0 = texture(texUnit0, vec2(0.625, 0.375));
	results[0] = (search0.y == 6.10);

	vec4 search1 = textureLod(texUnit0, vec2(0.625, 0.375), 0.0);
	results[1] = (search1.y == 6.10);

	vec4 search2 = textureLod(texUnit0, vec2(0.75, 0.75), 1.0);
	results[2] = (search2.y == 3.11);

	ivec4 search3 = texture(texUnit1, vec2(0.625, 0.375));
	results[3] = (search3.y == 610);

	uvec4 search4 = texture(texUnit2, vec2(0.625, 0.375));
	results[4] = (search4.y == 610u);

	vec4 search5 = texture(texUnit3, vec3(0.625, 0.375, 0.125));
	results[5] = (search5.y == 6.10);

	vec4 search6 = texture(texUnit3, vec3(0.625, 0.375, 0.375));
	results[6] = (search6.y == 22.10);

	vec4 search7 = textureLod(texUnit3, vec3(0.75, 0.75, 0.25), 1.0);
	results[7] = (search7.y == 3.11);

	ivec4 search8 = texture(texUnit4, vec3(0.625, 0.375, 0.125));
	results[8] = (search8.y == 610);

	uvec4 search9 = texture(texUnit5, vec3(0.625, 0.375, 0.125));
	results[9] = (search9.y == 610u);
	
	vec4 search10 = texture(texUnit6, vec3(0.625, 0.375, 1.0));
	results[10] = (search10.y == 22.10);

	vec4 search11 = textureLod(texUnit6, vec3(0.75, 0.75, 1.0), 1.0);
	results[11] = (search11.y == 7.11);

	ivec4 search12 = texture(texUnit7, vec3(0.625, 0.375, 1.0));
	results[12] = (search12.y == 2210);

	uvec4 search13 = texture(texUnit8, vec3(0.625, 0.375, 1.0));
	results[13] = (search13.y == 2210u);

	vec4 search14 = texture(texUnit9, vec3(0.375 - 0.5, 0.125 - 0.5, -0.5));
	results[14] = (search14.y == 14.1);

	vec4 search15 = textureLod(texUnit9, vec3(0.75 - 0.5, 0.25 - 0.5, -0.5), 1.0);
	results[15] = (search15.y == 2.11);

	ivec4 search16 = texture(texUnit10, vec3(0.375 - 0.5, 0.125 - 0.5, -0.5));
	results[16] = (search16.y == 1410);

	ivec4 search17 = textureLod(texUnit10, vec3(0.75 - 0.5, 0.25 - 0.5, -0.5), 1.0);
	results[17] = (search17.y == 211);

	uvec4 search18 = texture(texUnit11, vec3(0.375 - 0.5, 0.125 - 0.5, -0.5));
	results[18] = (search18.y == 1410u);

	uvec4 search19 = textureLod(texUnit11, vec3(0.75 - 0.5, 0.25 - 0.5, -0.5), 1.0);
	results[19] = (search19.y == 211u);

	ivec2 search20 = textureSize(texUnit0, 1); //2D
	results[20] = (search20 == ivec2(2, 2));

	ivec2 search21 = textureSize(texUnit1, 1);
	results[21] = (search21 == ivec2(2, 2));

	ivec2 search22 = textureSize(texUnit2, 1);
	results[22] = (search22 == ivec2(2, 2));

	ivec3 search23 = textureSize(texUnit3, 1); //3D
	results[23] = (search23 == ivec3(2, 2, 2));

	ivec3 search24 = textureSize(texUnit4, 1);
	results[24] = (search24 == ivec3(2, 2, 2));

	ivec3 search25 = textureSize(texUnit5, 1);
	results[25] = (search25 == ivec3(2, 2, 2));

	ivec3 search26 = textureSize(texUnit6, 1); //2DArray
	results[26] = (search26 == ivec3(2, 2, 4));

	ivec3 search27 = textureSize(texUnit7, 1);
	results[27] = (search27 == ivec3(2, 2, 4));

	ivec3 search28 = textureSize(texUnit8, 1);
	results[28] = (search28 == ivec3(2, 2, 4));

	ivec2 search29 = textureSize(texUnit9, 1); //Cube
	results[29] = (search29 == ivec2(2, 2));

	ivec2 search30 = textureSize(texUnit10, 1);
	results[30] = (search30 == ivec2(2, 2));

	ivec2 search31 = textureSize(texUnit11, 1);
	results[31] = (search31 == ivec2(2, 2));









	gl_Position = vec4(vPosition.x / 16.0, float(results[gl_VertexID]) / 2.0, vPosition.z, 1.0);
//	gl_Position = vec4(vPosition.x / 16.0, float(search21.x) / 2.0 , vPosition.z, 1.0);

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
