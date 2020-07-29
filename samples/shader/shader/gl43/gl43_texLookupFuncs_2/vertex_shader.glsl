#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
uniform highp sampler2DShadow texUnit0;
uniform highp sampler2DArrayShadow texUnit1;
uniform highp samplerCubeShadow texUnit2;


out vec4 vfColor;


void main()
{

	bool results[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);
	float search0 = texture(texUnit0, vec3(0.625, 0.375, 0.060)); 
	results[0] = (search0 == 1.0);
	float search1 = texture(texUnit0, vec3(0.625, 0.375, 0.061)); 
	results[1] = (search1 == 0.0);
	float search2 = textureLod(texUnit0, vec3(0.25, 0.75, 0.021), 1.0); 
	results[2] = (search2 == 1.0);
	float search3 = textureLod(texUnit0, vec3(0.25, 0.75, 0.0211), 1.0); 
	results[3] = (search3 == 0.0);

	float search4 = texture(texUnit1, vec4(0.625, 0.375, 0.0, 0.060));  // the third arguement is layer
	results[4] = (search4 == 1.0);
	float search5 = texture(texUnit1, vec4(0.625, 0.375, 0.0, 0.061)); 
	results[5] = (search5 == 0.0);

	float search6 = texture(texUnit2, vec4(0.375 - 0.5, 0.125 - 0.5, -0.5, 0.14)); 
	results[6] = (search6 == 1.0);
	float search7 = texture(texUnit2, vec4(0.375 - 0.5, 0.125 - 0.5, -0.5, 0.141)); 
	results[7] = (search7 == 0.0);

	ivec2 search8 = textureSize(texUnit0, 1); 
	results[8] = (search8 == ivec2(2, 2));
	ivec3 search9 = textureSize(texUnit1, 1); 
	results[9] = (search9 == ivec3(2, 2, 4));
	ivec2 search10 = textureSize(texUnit2, 1);
	results[10] = (search10 == ivec2(2, 2));

	float search11 = textureProj(texUnit0, 2.0 * vec4(0.625, 0.375, 0.060, 1.0)); 
	results[11] = (search11 == 1.0);
	float search12 = textureProj(texUnit0, 2.0 * vec4(0.625, 0.375, 0.061, 1.0)); 
	results[12] = (search12 == 0.0);

	float search13 = textureOffset(texUnit0, vec3(0.625, 0.375, (0.060 + 0.01)), ivec2(1, 0)); 
	results[13] = (search13 == 1.0);
	float search14 = textureOffset(texUnit0, vec3(0.625, 0.375, (0.061 + 0.01)), ivec2(1, 0)); 
	results[14] = (search14 == 0.0);

	float search15 = textureProjOffset(texUnit0, 2.0 * vec4(0.625, 0.375, (0.060 + 0.01), 1.0), ivec2(1, 0));
	results[15] = (search15 == 1.0);
	float search16 = textureProjOffset(texUnit0, 2.0 * vec4(0.625, 0.375, (0.061 + 0.01), 1.0), ivec2(1, 0)); 
	results[16] = (search16 == 0.0);

	float search17 = textureLodOffset(texUnit0, vec3(0.25, 0.75, (0.021 + 0.01)), 1.0, ivec2(1, 0)); 
	results[17] = (search17 == 1.0);
	float search18 = textureLodOffset(texUnit0, vec3(0.25, 0.75, (0.0211 + 0.01)), 1.0, ivec2(1, 0));
	results[18] = (search18 == 0.0);

	float search19 = textureProjLod(texUnit0, 2.0 * vec4(0.625, 0.375, 0.060, 1.0), 0.0); 
	results[19] = (search19 == 1.0);
	float search20 = textureProjLod(texUnit0, 2.0 * vec4(0.625, 0.375, 0.061, 1.0), 0.0); 
	results[20] = (search20 == 0.0);

	float search21 = textureProjLodOffset(texUnit0, 2.0 * vec4(0.625, 0.375, (0.060 + 0.01), 1.0), 0.0, ivec2(1, 0)); 
	results[21] = (search21 == 1.0);
	float search22 = textureProjLodOffset(texUnit0, 2.0 * vec4(0.625, 0.375, (0.061 + 0.01), 1.0), 0.0, ivec2(1, 0)); 
	results[22] = (search22 == 0.0);



	float search23 = textureGrad(texUnit0, vec3(0.625, 0.375, 0.060), vec2(0.01, 0.02), vec2(0.03, 0.04)); 
	results[23] = (search23 == 1.0);
	float search24 = textureGrad(texUnit0, vec3(0.625, 0.375, 0.061), vec2(0.01, 0.02), vec2(0.03, 0.04)); 
	results[24] = (search24 == 0.0);


	float search25 = textureGrad(texUnit1, vec4(0.625, 0.375, 0.0, 0.060), vec2(0.01, 0.02), vec2(0.03, 0.04));  // the third arguement is layer
	results[25] = (search25 == 1.0);
	float search26 = textureGrad(texUnit1, vec4(0.625, 0.375, 0.0, 0.061), vec2(0.01, 0.02), vec2(0.03, 0.04)); 
	results[26] = (search26 == 0.0);

	float search27 = textureGrad(texUnit2, vec4(0.375 - 0.5, 0.125 - 0.5, -0.5, 0.14), vec3(0.1, 0.2, 0.5), vec3(0.3, 0.4, 0.6)); 
	results[27] = (search27 == 1.0);
	float search28 = textureGrad(texUnit2, vec4(0.375 - 0.5, 0.125 - 0.5, -0.5, 0.141), vec3(0.1, 0.2, 0.5), vec3(0.3, 0.4, 0.6)); 
	results[28] = (search28 == 0.0);



	float search29 = textureGradOffset(texUnit0, vec3(0.625, 0.375, (0.060 + 0.01)), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0)); 
	results[29] = (search29 == 1.0);
	float search30 = textureGradOffset(texUnit0, vec3(0.625, 0.375, (0.061 + 0.01)), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0)); 
	results[30] = (search30 == 0.0);


















	gl_Position = vec4(vPosition.x / 16.0, float(results[gl_VertexID]) / 2.0, vPosition.z, 1.0);
//	gl_Position = vec4(vPosition.x / 16.0, float(search6) / 1.0 , vPosition.z, 1.0);

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
