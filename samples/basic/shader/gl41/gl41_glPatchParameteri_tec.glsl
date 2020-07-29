#version 430 core  ///GLSL Version 3.20

#extension GL_ARB_ES3_2_compatibility : enable

layout (vertices = 3) out ;
in vec4 vtcColor[];
out vec4 tcteColor[];


void main()
{

	if(gl_PatchVerticesIn == 3){
		gl_TessLevelOuter[0] = 6.0;
		gl_TessLevelOuter[1] = 5.0;
		gl_TessLevelOuter[2] = 8.0;
		gl_TessLevelInner[0] = 5.0;
	}

	gl_BoundingBox[0] = vec4(-0.5, -1.0, -1.0, 1.0);
	gl_BoundingBox[1] = vec4(0.5, 1.0, 1.0, 1.0);

	
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;



	tcteColor[gl_InvocationID] = vtcColor[gl_InvocationID];

}

