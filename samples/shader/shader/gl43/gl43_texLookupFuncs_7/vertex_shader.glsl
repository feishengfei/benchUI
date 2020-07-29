#version      ///GLSL Version 3.20

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



	vec4 search0 = textureGather(texUnit9, vec3(0.625 - 0.5, 0.375 - 0.5, -0.5), 0);
	results[0] = (search0 == vec4(13.00, 14.00, 10.00, 9.00));

	ivec4 search1 = textureGather(texUnit10, vec3(0.625 - 0.5, 0.375 - 0.5, -0.5), 0);
	results[1] = (search1 == ivec4(1300, 1400, 1000, 900));

	uvec4 search2 = textureGather(texUnit11, vec3(0.625 - 0.5, 0.375 - 0.5, -0.5), 0);
	results[2] = (search2 == uvec4(1300u, 1400u, 1000u, 900u));


	vec4 search3 = textureGatherOffset(texUnit0, vec2(0.625, 0.375), ivec2(-1, 0), 0);
	results[3] = (search3 == vec4((10.00 - 1.00), (11.00 - 1.00), (7.00 - 1.00), (6.00 - 1.00)));

	ivec4 search4 = textureGatherOffset(texUnit1, vec2(0.625, 0.375), ivec2(-1, 0), 0);
	results[4] = (search4 == ivec4((1000 - 100), (1100 - 100), (700 - 100), (600 - 100)));

	uvec4 search5 = textureGatherOffset(texUnit2, vec2(0.625, 0.375), ivec2(-1, 0), 0);
	results[5] = (search5 == uvec4((1000u -100u), (1100u -100u), (700u -100u), (600u -100u)));

	vec4 search6 = textureGatherOffset(texUnit6, vec3(0.625, 0.375, 1.0), ivec2(-1, 0), 0);
	results[6] = (search6 == vec4((26.00 - 1.0), (27.00 - 1.0), (23.00 - 1.0), (22.00 - 1.0)));

	ivec4 search7 = textureGatherOffset(texUnit7, vec3(0.625, 0.375, 1.0), ivec2(-1, 0), 0);
	results[7] = (search7 == ivec4((2600 - 100), (2700 - 100), (2300 - 100), (2200 - 100)));

	uvec4 search8 = textureGatherOffset(texUnit8, vec3(0.625, 0.375, 1.0), ivec2(-1, 0), 0);
	results[8] = (search8 == uvec4((2600u - 100u), (2700u - 100u), (2300u - 100u), (2200u - 100u)));



	vec4 search9 = textureGatherOffsets(texUnit0, vec2(0.625, 0.375), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0)), 0);
	results[9] = (search9 == vec4((6.00 + 1.00), (6.00 - 1.00), (6.00 - 1.00), (6.00 - 1.00)));

	ivec4 search10 = textureGatherOffsets(texUnit1, vec2(0.625, 0.375), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0)), 0);
	results[10] = (search10 == ivec4((600 + 100), (600 - 100), (600 - 100), (600 - 100)));

	uvec4 search11 = textureGatherOffsets(texUnit2, vec2(0.625, 0.375), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0)), 0);
	results[11] = (search11 == uvec4((600u + 100u), (600u - 100u), (600u -100u), (600u -100u)));

	vec4 search12 = textureGatherOffsets(texUnit6, vec3(0.625, 0.375, 1.0), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0)), 0);
	results[12] = (search12 == vec4((22.00 + 1.0), (22.00 - 1.0), (22.00 - 1.0), (22.00 - 1.0)));

	ivec4 search13 = textureGatherOffsets(texUnit7, vec3(0.625, 0.375, 1.0), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0)), 0);
	results[13] = (search13 == ivec4((2200 + 100), (2200 - 100), (2200 - 100), (2200 - 100)));

	uvec4 search14 = textureGatherOffsets(texUnit8, vec3(0.625, 0.375, 1.0), ivec2[4](ivec2(1, 0), ivec2(-1, 0), ivec2(-1, 0), ivec2(-1, 0)), 0);
	results[14] = (search14 == uvec4((2200u + 100u), (2200u - 100u), (2200u - 100u), (2200u - 100u)));












	



	











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
