#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

layout (local_size_x = 10, local_size_y = 10, local_size_z = 1) in;


layout (binding = 0, r32f) uniform coherent volatile highp image2D imageUnit0;
layout (binding = 1, r32i) uniform coherent volatile highp iimage2D imageUnit1;
layout (binding = 2, r32ui) uniform highp uimage2D imageUnit2;
layout (binding = 3, r32f) uniform highp image3D imageUnit3;
layout (binding = 4, r32i) uniform highp iimage3D imageUnit4;
layout (binding = 5, r32ui) uniform highp uimage3D imageUnit5;

void main()
{		
	
					for(int i = 0; i < 1000; i++){
							imageStore(imageUnit0, ivec2(1, 0), vec4(1.5, 0.0, 0.0, 0.0));
					}
					imageStore(imageUnit0, ivec2(1, 0), vec4(1.6, 0.0, 0.0, 0.0));

					memoryBarrier();
					barrier();

					vec4 temp = imageLoad(imageUnit0, ivec2(1, 0));
					if(1.5 == temp.x){
						imageStore(imageUnit0, ivec2(2, 0), vec4(2.1, 0.0, 0.0, 0.0));
					}




					for(int i = 0; i < 1000; i++){
							imageStore(imageUnit1, ivec2(1, 0), ivec4(150, 0, 0, 0));
					}
					imageStore(imageUnit1, ivec2(1, 0), ivec4(160, 0, 0, 0));

					memoryBarrierImage();
					barrier();

					ivec4 temp2 = imageLoad(imageUnit1, ivec2(1, 0));
					if(150 == temp2.x){
						imageStore(imageUnit1, ivec2(2, 0), ivec4(210, 0, 0, 0));
					}



					for(int i = 0; i < 1000; i++){
							imageStore(imageUnit2, ivec2(1, 0), uvec4(150u, 0u, 0u, 0u));
					}
					imageStore(imageUnit2, ivec2(1, 0), uvec4(160u, 0u, 0u, 0u));

					groupMemoryBarrier();
					barrier();

					uvec4 temp3 = imageLoad(imageUnit2, ivec2(1, 0));
					if(150u == temp3.x){
						imageStore(imageUnit2, ivec2(2, 0), uvec4(210u, 0, 0, 0));
					}
					
}

