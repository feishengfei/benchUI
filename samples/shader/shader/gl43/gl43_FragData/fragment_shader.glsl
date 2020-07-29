#version         //GLSL Version 3.20; OpenGL es 3.2

precision highp float;
in vec4 vfColor;
out vec4 FragColor;


void main()
{		
//	gl_FragData[0] = vfColor;
	FragColor = vfColor;
}
