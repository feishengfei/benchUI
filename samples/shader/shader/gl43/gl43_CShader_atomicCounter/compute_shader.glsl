#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

layout (local_size_x = 10, local_size_y = 10, local_size_z = 1) in;

layout (binding = 0, offset = 0) uniform atomic_uint atomicNum;
layout (binding = 0, offset = 4) uniform atomic_uint atomicDecrease;
layout (binding = 0, offset = 8) uniform atomic_uint atomicIncrease;


void main()
{		
	

					uint ac2 = atomicCounterIncrement(atomicIncrease);

					memoryBarrierAtomicCounter();
					barrier();

					uint ac0 = atomicCounter(atomicIncrease);
					if(ac0 < 600u){
						atomicCounterIncrement(atomicNum);
					}

}

