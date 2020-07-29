#version 430 core

layout(location = 0) in vec2 VsInPos;
layout(location = 1) in vec3 VsInColor;

out vec4 color;

void main()
{
	gl_Position = vec4(VsInPos, 0.0, 1.0);
	color = vec4(VsInColor, 1.0);
}


