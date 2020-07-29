#version            ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
out vec4 vfColor;

void main()
{


	if(gl_VertexID < 10)
		gl_Position = vec4(vPosition.x / 16.0, 1.0 / 2.0, vPosition.z, 1.0);
	else if(gl_VertexID < 20)
		gl_Position = vec4(vPosition.x / 16.0, 1.1 / 2.0, vPosition.z, 1.0);
	else 
		gl_Position = vec4(vPosition.x / 16.0, 1.2 / 2.0, vPosition.z, 1.0);

//	gl_Position = vec4(vPosition.x / 16.0, float(results[gl_VertexID]) / 2.0, vPosition.z, 1.0);
//	gl_Position = vec4(vPosition.x / 16.0, col.x / 2.0, vPosition.z, 1.0);

	vfColor = vColor;

	gl_PointSize = 10.0;
}

// 0x10000u = 2^16
// in packUnorm2x16(vec2(vPosition.x, 0.5)), vPosition.x is the lower part, 0.5 is the higher part
