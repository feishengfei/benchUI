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
					imageAtomicXor(imageUnit1, ivec3(1, 0, 0), 0xFFFFFFFF);
					ivec4 col_0 = imageLoad(imageUnit1, ivec3(1, 0, 0));
					results[0] = (col_0.x == 100  ||  col_0.x == (~100));
		} break;
		case 1:{
					imageAtomicXor(imageUnit2, ivec3(1, 0, 0), 0xFFFFFFFFu);
					uvec4 col_1 = imageLoad(imageUnit2, ivec3(1, 0, 0));
					results[1] = (col_1.x == 100u  ||  col_1.x == (~(100u)));
		} break;
		case 2:{
					imageAtomicXor(imageUnit4, ivec3(1, 0, 0), 0xFFFFFFFF);
					ivec4 col_2 = imageLoad(imageUnit4, ivec3(1, 0, 0));
					results[2] = (col_2.x == 100  ||  col_2.x == (~100));
		} break;
		case 3:{
					imageAtomicXor(imageUnit5, ivec3(1, 0, 0), 0xFFFFFFFFu);
					uvec4 col_3 = imageLoad(imageUnit5, ivec3(1, 0, 0));
					results[3] = (col_3.x == 100u  ||  col_3.x == (~(100u)));
		} break;


		case 4:{
//					imageAtomicExchange(imageUnit0, ivec3(2, 0, 0), 2.1);
					vec4 col_4 = imageLoad(imageUnit0, ivec3(2, 0, 0));
					results[4] = (col_4.x == 2.1);
		} break;
		case 5:{
//					imageAtomicExchange(imageUnit1, ivec3(2, 0, 0), 210);
					ivec4 col_5 = imageLoad(imageUnit1, ivec3(2, 0, 0));
					results[5] = (col_5.x == 210);
		} break;
		case 6:{
					imageAtomicExchange(imageUnit2, ivec3(2, 0, 0), 210u);
					uvec4 col_6 = imageLoad(imageUnit2, ivec3(2, 0, 0));
					results[6] = (col_6.x == 210u);
		} break;	


		case 7:{
//					imageAtomicExchange(imageUnit3, ivec3(2, 0, 0), 2.1);
					vec4 col_7 = imageLoad(imageUnit3, ivec3(2, 0, 0));
					results[7] = (col_7.x == 2.1);
		} break;
		case 8:{
//					imageAtomicExchange(imageUnit4, ivec3(2, 0, 0), 210);
					ivec4 col_8 = imageLoad(imageUnit4, ivec3(2, 0, 0));
					results[8] = (col_8.x == 210);
		} break;
		case 9:{
					imageAtomicExchange(imageUnit5, ivec3(2, 0, 0), 210u);
					uvec4 col_9 = imageLoad(imageUnit5, ivec3(2, 0, 0));
					results[9] = (col_9.x == 210u);
		} break;


		case 10:{
					imageAtomicCompSwap(imageUnit1, ivec3(3, 0, 0), 300, 301);
					ivec4 col_10 = imageLoad(imageUnit1, ivec3(3, 0, 0));
					results[10] = (col_10.x == 301);
		} break;
		case 11:{
					imageAtomicCompSwap(imageUnit2, ivec3(3, 0, 0), 300u, 301u);
					uvec4 col_11 = imageLoad(imageUnit2, ivec3(3, 0, 0));
					results[11] = (col_11.x == 301u);
		} break;	
		case 12:{
					imageAtomicCompSwap(imageUnit4, ivec3(3, 0, 0), 300, 301);
					ivec4 col_12 = imageLoad(imageUnit4, ivec3(3, 0, 0));
					results[12] = (col_12.x == 301);
		} break;
		case 13:{
					imageAtomicCompSwap(imageUnit5, ivec3(3, 0, 0), 300u, 301u);
					uvec4 col_13 = imageLoad(imageUnit5, ivec3(3, 0, 0));
					results[13] = (col_13.x == 301u);
		} break;

		default: break;
	}


	if(results[gl_PrimitiveID] == true)
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;

}
