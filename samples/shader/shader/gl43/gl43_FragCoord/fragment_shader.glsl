#version  //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in vec4 vfColor;

in vec4 vfFunc;
in vec3 vfFunc_3;
in vec2 vfFunc_2;
in float vfFunc_1;

layout(location = 0) uniform int NumSamples;

out vec4 FragColor;

void main()
{	

	if(gl_FragCoord.x <= 300.0 || gl_FragCoord.y >= 300.0)
		FragColor = vfColor + vfFunc * 0.00000001;
	else
		FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
