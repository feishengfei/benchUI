#version   ///GLSL Version 3.20

in vec4 vPosition;
in vec4 vColor;
in vec4 vFunc;



out vec4 vfColor;
out vec4 vfFunc;
out vec3 vfFunc_3;
out vec2 vfFunc_2;
out float vfFunc_1;


void main()
{
	
	mat4 mvp = mat4	(
							1.0, 0.0, 0.0, 0.0,
							0.0, 1.0, 0.0, 0.0,
							0.0, 0.0, 1.0, 0.0,
							0.0, 0.0, 0.0, 1.0
						);
	gl_Position = mvp * vPosition;
	
	vfColor = vColor;
	vfFunc = vFunc;
	vfFunc_3 = vFunc.xyz;
	vfFunc_2 = vFunc.xy;
	vfFunc_1 = vFunc.x;
}

