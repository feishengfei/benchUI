#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

layout (local_size_x = 10, local_size_y = 10, local_size_z = 1) in;

layout (std430, binding = 0) buffer BufferObject
{
	int int_var[8];
	uint uint_var[8];
} ssbo ;

shared int p;


void main()
{
		
				for(int i = 0; i < 100000; i++){
					p = 1;
				}
				p = 2;
					

				memoryBarrierShared();
				barrier();

				if(p == 1){
					ssbo.uint_var[0] = 9u;
				}

}

