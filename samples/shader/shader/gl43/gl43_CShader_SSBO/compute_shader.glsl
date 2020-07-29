#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

layout (local_size_x = 10, local_size_y = 10, local_size_z = 1) in;

layout (std430, binding = 0) buffer BufferObject
{
	int int_var[8];
	uint uint_var[8];
} ssbo ;


void main()
{		
				for(int i = 0; i < 1000; i++){
					ssbo.int_var[0] = -1;
				}
				ssbo.int_var[0] = -2;
					

				memoryBarrierBuffer();
				barrier();

				if(ssbo.int_var[0] == -1){
					ssbo.uint_var[0] = 9u;
				}

}

