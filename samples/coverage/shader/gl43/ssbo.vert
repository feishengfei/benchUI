#version 430 core

layout(location = 0)in vec4 vPosition;
layout(location = 1)in vec4 vColor;
out vec4 vfColor;

void main()
{


	if(gl_VertexID < 10)
		gl_Position = vec4(vPosition.x / 16.0, 1.0 / 2.0, vPosition.z, 1.0);
	else if(gl_VertexID < 20)
		gl_Position = vec4(vPosition.x / 16.0, 1.1 / 2.0, vPosition.z, 1.0);
	else 
		gl_Position = vec4(vPosition.x / 16.0, 1.2 / 2.0, vPosition.z, 1.0);

	vfColor = vColor;

	gl_PointSize = 10.0;
}
