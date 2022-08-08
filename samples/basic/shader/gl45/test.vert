#version 430 core




layout(location = 0) in vec4 VsInPos;
layout(location = 1) in vec4 VsInColor;

out flat ivec4 color;

void main()
{
	gl_Position = VsInPos;
	color = ivec4(VsInColor);
}


