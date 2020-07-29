#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;
in vec4 vfColor;

layout (binding = 0, r32f) uniform highp imageCube imageUnit0;
layout (binding = 1, r32i) uniform highp iimageCube imageUnit1;
layout (binding = 2, r32ui) uniform highp uimageCube imageUnit2;
layout (binding = 3, r32f) uniform highp image2DArray imageUnit3;
layout (binding = 4, r32i) uniform highp iimage2DArray imageUnit4;
layout (binding = 5, r32ui) uniform highp uimage2DArray imageUnit5;

out vec4 FragColor;



void main()
{		
	
	bool results[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);
	switch (gl_PrimitiveID){
		case 0:{
					imageStore(imageUnit0, ivec3(1, 0, 0), vec4(1.5, 0.0, 0.0, 0.0));
					vec4 col_0 = imageLoad(imageUnit0, ivec3(1, 0, 0));
					results[0] = (col_0.x == 1.5);
		} break;
		case 1:{
					imageStore(imageUnit1, ivec3(1, 0, 0), ivec4(150, 0, 0, 0));
					ivec4 col_1 = imageLoad(imageUnit1, ivec3(1, 0, 0));
					results[1] = (col_1.x == 150);
		} break;
		case 2:{
					imageStore(imageUnit2, ivec3(1, 0, 0), uvec4(150u, 0u, 0u, 0u));
					uvec4 col_2 = imageLoad(imageUnit2, ivec3(1, 0, 0));
					results[2] = (col_2.x == 150u);
		} break;
		case 3:{
					imageStore(imageUnit3, ivec3(1, 0, 0), vec4(1.5, 0.0, 0.0, 0.0));
					vec4 col_3 = imageLoad(imageUnit3, ivec3(1, 0, 0));
					results[3] = (col_3.x == 1.5);
		} break;
		case 4:{
					imageStore(imageUnit4, ivec3(1, 0, 0), ivec4(150, 0, 0, 0));
					ivec4 col_4 = imageLoad(imageUnit4, ivec3(1, 0, 0));
					results[4] = (col_4.x == 150);
		} break;
		case 5:{
					imageStore(imageUnit5, ivec3(1, 0, 0), uvec4(150u, 0u, 0u, 0u));
					uvec4 col_5 = imageLoad(imageUnit5, ivec3(1, 0, 0));
					results[5] = (col_5.x == 150u);
		} break;
		case 6:{
					ivec2 col_6 = imageSize(imageUnit0);
					results[6] = (col_6 == ivec2(4, 4));
		} break;
		case 7:{
					ivec2 col_7 = imageSize(imageUnit1);
					results[7] = (col_7 == ivec2(4, 4));
		} break;
		case 8:{
					ivec2 col_8 = imageSize(imageUnit2);
					results[8] = (col_8 == ivec2(4, 4));
		} break;
		case 9:{
					ivec3 col_9 = imageSize(imageUnit3);
					results[9] = (col_9 == ivec3(4, 4, 4));
		} break;
		case 10:{
					ivec3 col_10 = imageSize(imageUnit4);
					results[10] = (col_10 == ivec3(4, 4, 4));
		} break;
		case 11:{
					ivec3 col_11 = imageSize(imageUnit5);
					results[11] = (col_11 == ivec3(4, 4, 4));
		} break;
		case 12:{
					imageAtomicAdd(imageUnit1, ivec3(2, 0, 0), 1);
					ivec4 col_12 = imageLoad(imageUnit1, ivec3(2, 0, 0));
					results[12] = (col_12.x >= 201  && col_12.x <= 300);
		} break;
		case 13:{
					imageAtomicAdd(imageUnit2, ivec3(2, 0, 0), 1u);
					uvec4 col_13 = imageLoad(imageUnit2, ivec3(2, 0, 0));
					results[13] = (col_13.x >= 201u  && col_13.x <= 310u);		
		} break;
		case 14:{
					imageAtomicAdd(imageUnit4, ivec3(2, 0, 0), 1);
					ivec4 col_14 = imageLoad(imageUnit4, ivec3(2, 0, 0));
					results[14] = (col_14.x >= 201  && col_14.x <= 300);
		} break;
		case 15:{
					imageAtomicAdd(imageUnit5, ivec3(2, 0, 0), 1u);
					uvec4 col_15 = imageLoad(imageUnit5, ivec3(2, 0, 0));
					results[15] = (col_15.x >= 201u  && col_15.x <= 310u);		
		} break;
		case 16:{
					imageAtomicMin(imageUnit1, ivec3(3, 0, 0), 299);
					ivec4 col_16 = imageLoad(imageUnit1, ivec3(3, 0, 0));
					results[16] = (col_16.x == 299);
		} break;
		case 17:{
					imageAtomicMin(imageUnit2, ivec3(3, 0, 0), 299u);
					uvec4 col_17 = imageLoad(imageUnit2, ivec3(3, 0, 0));
					results[17] = (col_17.x == 299u);
		} break;
		case 18:{
					imageAtomicMin(imageUnit4, ivec3(3, 0, 0), 299);
					ivec4 col_18 = imageLoad(imageUnit4, ivec3(3, 0, 0));
					results[18] = (col_18.x == 299);
		} break;
		case 19:{
					imageAtomicMin(imageUnit5, ivec3(3, 0, 0), 299u);
					uvec4 col_19 = imageLoad(imageUnit5, ivec3(3, 0, 0));
					results[19] = (col_19.x == 299u);
		} break;
		case 20:{
					imageAtomicMax(imageUnit1, ivec3(0, 1, 0), 401);
					ivec4 col_20 = imageLoad(imageUnit1, ivec3(0, 1, 0));
					results[20] = (col_20.x == 401);
		} break;
		case 21:{
					imageAtomicMax(imageUnit2, ivec3(0, 1, 0), 401u);
					uvec4 col_21 = imageLoad(imageUnit2, ivec3(0, 1, 0));
					results[21] = (col_21.x == 401u);
		} break;
		case 22:{
					imageAtomicMax(imageUnit4, ivec3(0, 1, 0), 401);
					ivec4 col_22 = imageLoad(imageUnit4, ivec3(0, 1, 0));
					results[22] = (col_22.x == 401);
		} break;
		case 23:{
					imageAtomicMax(imageUnit5, ivec3(0, 1, 0), 401u);
					uvec4 col_23 = imageLoad(imageUnit5, ivec3(0, 1, 0));
					results[23] = (col_23.x == 401u);
		} break;
		case 24:{
					imageAtomicAnd(imageUnit1, ivec3(1, 1, 0), 0x0000000F);
					ivec4 col_24 = imageLoad(imageUnit1, ivec3(1, 1, 0));
					results[24] = (col_24.x >= 4);
		} break;
		case 25:{
					imageAtomicAnd(imageUnit2, ivec3(1, 1, 0), 0x0000000Fu);
					uvec4 col_25 = imageLoad(imageUnit2, ivec3(1, 1, 0));
					results[25] = (col_25.x == 4u);
		} break;
		case 26:{
					imageAtomicAnd(imageUnit4, ivec3(1, 1, 0), 0x0000000F);
					ivec4 col_26 = imageLoad(imageUnit4, ivec3(1, 1, 0));
					results[26] = (col_26.x == 4);
		} break;
		case 27:{
					imageAtomicAnd(imageUnit5, ivec3(1, 1, 0), 0x0000000Fu);
					uvec4 col_27 = imageLoad(imageUnit5, ivec3(1, 1, 0));
					results[27] = (col_27.x == 4u);
		} break;
		case 28:{
					imageAtomicOr(imageUnit1, ivec3(2, 1, 0), 0x00000009);
					ivec4 col_28 = imageLoad(imageUnit1, ivec3(2, 1, 0));
					results[28] = (col_28.x == 601);
		} break;
		case 29:{
					imageAtomicOr(imageUnit2, ivec3(2, 1, 0), 0x00000009u);
					uvec4 col_29 = imageLoad(imageUnit2, ivec3(2, 1, 0));
					results[29] = (col_29.x == 601u);
		} break;
		case 30:{
					imageAtomicOr(imageUnit4, ivec3(2, 1, 0), 0x00000009);
					ivec4 col_30 = imageLoad(imageUnit4, ivec3(2, 1, 0));
					results[30] = (col_30.x == 601);
		} break;
		case 31:{
					imageAtomicOr(imageUnit5, ivec3(2, 1, 0), 0x00000009u);
					uvec4 col_31 = imageLoad(imageUnit5, ivec3(2, 1, 0));
					results[31] = (col_31.x == 601u);
		} break;


		default: break;
	}


	if(results[gl_PrimitiveID] == true)
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;

}
