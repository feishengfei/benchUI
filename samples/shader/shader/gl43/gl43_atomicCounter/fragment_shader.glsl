#version        //430

precision highp float;
in vec4 vfColor;
layout (binding = 0, offset = 0) uniform atomic_uint atomicNum;
layout (binding = 0, offset = 4) uniform atomic_uint atomicDecrease;
layout (binding = 0, offset = 8) uniform atomic_uint atomicIncrease;



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
					uint ac0 = atomicCounter(atomicNum);
					results[0] = (ac0 == 100u);
		} break;
		case 1:{
					uint ac1 = atomicCounterDecrement(atomicDecrease);
					results[1] = (ac1 >= 190u && ac1 <= 300u);
		} break;
		case 2:{
					uint ac2 = atomicCounterIncrement(atomicIncrease);
					results[2] = (ac2 >= 500u && ac2 <= 600u);
		} break;



		default: break;
	}



	if(results[gl_PrimitiveID] == true)
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	else
		FragColor = vfColor;

}
