#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
in vec4 vFunc;



out vec4 vfColor;
out vec4 vfFunc;


void main()
{
	gl_Position = vPosition;
	vfColor = vColor;
	vfFunc = vFunc;
}

