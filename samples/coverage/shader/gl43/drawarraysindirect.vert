#version 430 core

layout(location = 0) in vec2 pos;
layout(location = 1) in vec4 col;
layout(location = 2) in vec2 PosOffset;//每个实例更新一次

out vec4 oColor;

void main()
{
    vec2 position = pos + PosOffset;
	gl_Position =  vec4(position, 0.0, 1.0);
	oColor = col;
}

