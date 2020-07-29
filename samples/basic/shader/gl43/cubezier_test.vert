#version 430 core

layout(location = 0) in vec4 position;

out vec4 color;

void main()
{
	gl_Position = position;
}


