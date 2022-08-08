#version 430 core //GLSL Version 3.20; OpenGL es 3.2

precision highp float;

in vec4 tefColor;

out vec4 FragColor;

void main()
{	
			FragColor = tefColor;
}
