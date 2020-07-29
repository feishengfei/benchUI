#version           ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
in vec4 vFunc;



out vec4 vfColor;
sample out vec4 vfFunc;
sample out vec3 vfFunc_3;
sample out vec2 vfFunc_2;
sample out float vfFunc_1;


void main()
{
	gl_Position = vPosition;
	vfColor = vColor;
	vfFunc = vFunc;
	vfFunc_3 = vFunc.xyz;
	vfFunc_2 = vFunc.xy;
	vfFunc_1 = vFunc.x;

}

