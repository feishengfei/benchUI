#version 430 core

layout(location = 0) in vec4 position;
layout(location = 0) uniform mat4 mvp_matrix;

out vec4 color;

void main()
{
	gl_Position = mvp_matrix * position;
}


