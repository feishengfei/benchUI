#version 430 core  ///GLSL Version 3.20

//uniform float theta;
//uniform int choice;
in vec4 vPosition;
in vec4 vColor;

out vec4 vfColor;

void main()
{
	
	gl_Position = vec4(vPosition.x / 1.0, vPosition.y / 1.0, vPosition.z, 1.0);

	gl_PointSize = 64.0;

	vfColor = vColor;
}
