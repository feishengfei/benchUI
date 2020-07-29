#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

layout (local_size_x = 2, local_size_y = 2) in;


layout (binding = 0, r32f) uniform coherent volatile highp image2D imageUnit0;
layout (binding = 1, r32i) uniform coherent volatile highp iimage2D imageUnit1;
layout (binding = 2, r32ui) uniform coherent volatile highp uimage2D imageUnit2;
layout (binding = 3, r32f) uniform highp image3D imageUnit3;
layout (binding = 4, r32i) uniform highp iimage3D imageUnit4;
layout (binding = 5, r32ui) uniform highp uimage3D imageUnit5;

void main()
{		
	
if (
			gl_NumWorkGroups == uvec3(2u, 2u, 1u)
		&&	gl_GlobalInvocationID == gl_WorkGroupID * gl_WorkGroupSize + gl_LocalInvocationID
		&&	gl_LocalInvocationIndex ==    gl_LocalInvocationID.z * gl_WorkGroupSize.x * gl_WorkGroupSize.y 
												+ gl_LocalInvocationID.y * gl_WorkGroupSize.x	
												+ gl_LocalInvocationID.x
	)
{	
	ivec4 temp = ivec4(0, 0, 0, 0);
	for(int k = 0; k < 4; k++){
		ivec4 temp_i = imageLoad(imageUnit1, ivec2(gl_GlobalInvocationID.x, k));
		ivec4 temp_j = imageLoad(imageUnit1, ivec2(k, gl_GlobalInvocationID.y));
		temp += temp_i * temp_j;
	}	
	imageStore(imageUnit0, ivec2(gl_GlobalInvocationID.xy), vec4(temp));
}

					
}

