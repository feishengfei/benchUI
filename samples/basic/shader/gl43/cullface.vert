#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 0) uniform mat4 modelview;

out vec2 TexCoord;

void main()
{
	gl_Position = modelview * vec4(aPos, 1.0f);
	TexCoord = aTexCoord;
}