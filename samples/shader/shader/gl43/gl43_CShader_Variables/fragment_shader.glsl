#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in vec4 vfColor;
out vec4 FragColor;

layout (binding = 0, r32f)  uniform coherent volatile highp image2D imageUnit0;
layout (binding = 1, r32i) uniform coherent volatile highp iimage2D imageUnit1;
layout (binding = 2, r32ui) uniform highp uimage2D imageUnit2;
layout (binding = 3, r32f) uniform highp image3D imageUnit3;
layout (binding = 4, r32i) uniform highp iimage3D imageUnit4;
layout (binding = 5, r32ui) uniform highp uimage3D imageUnit5;




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
					vec4 col_0 = imageLoad(imageUnit0, ivec2(0, 0));
					results[0] = (col_0.x == 560000.0);
		} break;
		case 1:{
					vec4 col_1 = imageLoad(imageUnit0, ivec2(1, 1));
					results[1] = (col_1.x == 1740000.0);
		} break;
/*		case 2:{
					uvec4 col_2 = imageLoad(imageUnit2, ivec2(2, 0));
					results[2] = (col_2.x == 201u);
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
					imageAtomicAdd(imageUnit1, ivec2(2, 0), 1);
					ivec4 col_12 = imageLoad(imageUnit1, ivec2(2, 0));
					results[12] = (col_12.x >= 201  && col_12.x <= 300);
		} break;
		case 13:{
					imageAtomicAdd(imageUnit2, ivec2(2, 0), 1u);
					uvec4 col_13 = imageLoad(imageUnit2, ivec2(2, 0));
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





*/
		default: break;
	}



	if(results[gl_PrimitiveID] == true)
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;

}
