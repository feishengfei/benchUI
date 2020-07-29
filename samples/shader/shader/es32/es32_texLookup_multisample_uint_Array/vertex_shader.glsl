#version                   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
uniform highp usampler2DMSArray texUnit0;


out vec4 vfColor;


void main()
{

	bool results[32] = bool[32](
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false,
					false,false,false,false,false,false,false,false
				);
	uvec4 search0 = texelFetch(texUnit0, ivec3(1, 1, 1), 0);
	results[0] = (search0 == uvec4(9u - 1u, 5u - 1u, 1u - 1u, 10u - 1u));

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
