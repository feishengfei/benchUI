#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 0) uniform mat4 modelview;

out vec3 TexCoord;

void main()
{
	gl_Position = modelview * vec4(aPos, 1.0f);
	//gl_Position = pos.xyww;
	//gl_Position = vec4(aPos, 1.0f);
	TexCoord = aPos;
}