#version 430 core

precision highp float;
in vec4 vfColor;

layout (std430, binding = 0) buffer BufferObject
{
	int int_var[8];
	uint uint_var[8];
} ssbo ;

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
					atomicAdd(ssbo.int_var[0], 1);
					results[0] = (ssbo.int_var[0] >= 1 && ssbo.int_var[0] <= 50);
		} break;
		case 1:{
					atomicAdd(ssbo.uint_var[0], 1u);
					results[1] = (ssbo.uint_var[0] >= 11u && ssbo.uint_var[0] <= 120u);
		} break;
		case 2:{
					atomicMin(ssbo.int_var[1], 0);
					results[2] = (ssbo.int_var[1] == 0);
		} break;
		case 3:{
					atomicMin(ssbo.uint_var[1], 9u);
					results[3] = (ssbo.uint_var[1] == 9u);
		} break;
		case 4:{
					atomicMax(ssbo.int_var[2], 3);
					results[4] = (ssbo.int_var[2] == 3);
		} break;
		case 5:{
					atomicMax(ssbo.uint_var[2], 13u);
					results[5] = (ssbo.uint_var[2] == 13u);
		} break;
		case 6:{
					atomicAnd(ssbo.int_var[3], 0x2);
					results[6] = (ssbo.int_var[3] == 2);
		} break;
		case 7:{
					atomicAnd(ssbo.uint_var[3], 0x6u);
					results[7] = (ssbo.uint_var[3] == 4u);
		} break;
		case 8:{
					atomicOr(ssbo.int_var[4], 0x2);
					results[8] = (ssbo.int_var[4] == 6);
		} break;
		case 9:{
					atomicOr(ssbo.uint_var[4], 0x1u);
					results[9] = (ssbo.uint_var[4] == 15u);
		} break;
/*		case 10:{
					atomicXor(ssbo.int_var[5], 5);
					results[10] = (ssbo.int_var[5] == 5 || ssbo.int_var[5] == 0);
		} break;
		case 11:{
					atomicXor(ssbo.uint_var[5], 15u);
					results[11] = (ssbo.uint_var[5] == 15u || ssbo.uint_var[5] == 0u);
		} break;
*/
		case 10:{
					atomicXor(ssbo.int_var[5], 0xFFFFFFFF);
					results[10] = (ssbo.int_var[5] == 5 || ssbo.int_var[5] == (~5));
		} break;
		case 11:{
					atomicXor(ssbo.uint_var[5], 0xFFFFFFFFu);
					results[11] = (ssbo.uint_var[5] == 15u || ssbo.uint_var[5] == (~(15u)));
		} break;
		case 12:{
					atomicExchange(ssbo.int_var[6], 1);
					results[12] = (ssbo.int_var[6] == 1);
		} break;
		case 13:{
					atomicExchange(ssbo.uint_var[6], 11u);
					results[13] = (ssbo.uint_var[6] == 11u);
		} break;
		case 14:{
					atomicCompSwap(ssbo.int_var[7], 7, 2);
					results[14] = (ssbo.int_var[7] == 2);
		} break;
		case 15:{
					atomicCompSwap(ssbo.uint_var[7], 17u, 2u);
					results[15] = (ssbo.uint_var[7] == 2u);
		} break;


		default: break;
	}



	if(results[gl_PrimitiveID] == true)
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;

}
