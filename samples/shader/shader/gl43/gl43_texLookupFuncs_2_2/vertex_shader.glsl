#version       ///GLSL Version 3.20

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

	float search0 = textureGradOffset(texUnit1, vec4(0.625, 0.375, 0.0, (0.060 + 0.01)), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0));  // the third arguement is layer
	results[0] = (search0 == 1.0);
	float search1 = textureGradOffset(texUnit1, vec4(0.625, 0.375, 0.0, (0.061 + 0.01)), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0)); 
	results[1] = (search1 == 0.0);

	float search2 = textureProjGrad(texUnit0, 2.0 * vec4(0.625, 0.375, 0.060, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04)); 
	results[2] = (search2 == 1.0);
	float search3 = textureProjGrad(texUnit0, 2.0 * vec4(0.625, 0.375, 0.061, 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04)); 
	results[3] = (search3 == 0.0);

	float search4= textureProjGradOffset(texUnit0, 2.0 * vec4(0.625, 0.375, (0.060 + 0.01), 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0)); 
	results[4] = (search4 == 1.0);
	float search5 = textureProjGradOffset(texUnit0, 2.0 * vec4(0.625, 0.375, (0.061 + 0.01), 1.0), vec2(0.01, 0.02), vec2(0.03, 0.04), ivec2(1, 0)); 
	results[5] = (search5 == 0.0);

	vec4 search6 = textureGather(texUnit0, vec2(0.625, 0.375), 0.060); 
	results[6] = (search6.w == 1.0);
	vec4 search7 = textureGather(texUnit0, vec2(0.625, 0.375), 0.061); 
	results[7] = (search7.w == 0.0);

	vec4 search8 = textureGather(texUnit1, vec3(0.625, 0.375, 0.0), 0.060); 
	results[8] = (search8.w == 1.0);
	vec4 search9 = textureGather(texUnit1, vec3(0.625, 0.375, 0.0), 0.061); 
	results[9] = (search9.w == 0.0);


	vec4 search10 = textureGather(texUnit2, vec3(0.625 - 0.5, 0.375 - 0.5, -0.5), 0.090); 
	results[10] = (search10.w == 1.0);
	vec4 search11 = textureGather(texUnit2, vec3(0.625 - 0.5, 0.375 - 0.5, -0.5), 0.091); 
	results[11] = (search11.w == 0.0);


	vec4 search12 = textureGatherOffset(texUnit0, vec2(0.625, 0.375), (0.060 + 0.010), ivec2(1, 0)); 
	results[12] = (search12.w == 1.0);
	vec4 search13 = textureGatherOffset(texUnit0, vec2(0.625, 0.375), (0.061 + 0.010), ivec2(1, 0)); 
	results[13] = (search13.w == 0.0);

	vec4 search14 = textureGatherOffset(texUnit1, vec3(0.625, 0.375, 0.0), (0.060 + 0.010), ivec2(1, 0)); 
	results[14] = (search14.w == 1.0);
	vec4 search15 = textureGatherOffset(texUnit1, vec3(0.625, 0.375, 0.0), (0.061 + 0.010), ivec2(1, 0)); 
	results[15] = (search15.w == 0.0);	


	vec4 search16 = textureGatherOffsets(texUnit0, vec2(0.625, 0.375), (0.060 - 0.010), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0))); 
	results[16] = (search16.w == 1.0);
	vec4 search17 = textureGatherOffsets(texUnit0, vec2(0.625, 0.375), (0.061 - 0.010), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0))); 
	results[17] = (search17.w == 0.0);

	vec4 search18 = textureGatherOffsets(texUnit1, vec3(0.625, 0.375, 0.0), (0.060 - 0.010), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0))); 
	results[18] = (search18.w == 1.0);
	vec4 search19 = textureGatherOffsets(texUnit1, vec3(0.625, 0.375, 0.0), (0.061 - 0.010), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0))); 
	results[19] = (search19.w == 0.0);	


















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
