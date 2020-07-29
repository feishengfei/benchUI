#version               ///GLSL Version 3.20

layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec4 vColor;

uniform highp isampler2DMSArray texUnit0;


out vec4 vfColor;


void main()
{

	bool results[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);
	ivec4 search0 = texelFetch(texUnit0, ivec3(1, 1, 1), 0);
	results[0] = (search0 == ivec4(9 - 1, 5 - 1, 1 - 1, 10 - 1));

	ivec3 search1 = textureSize(texUnit0);
	results[1] = (search1 == ivec3(4, 4, 2));












	gl_Position = vec4(vPosition.x / 16.0, float(results[gl_VertexID]) / 2.0, vPosition.z, 1.0);

	if(gl_VertexID < 10)
		vfColor = vColor;
	else if(gl_VertexID < 20)
		vfColor = vec4(0.0, 0.0, 1.0, 1.0);
	else
		vfColor = vec4(0.0, 1.0, 0.0, 1.0);
		
	gl_PointSize = 8.0;
}
