#version 430 core

layout(location = 0) in dvec4 vColor;
layout(location = 1) in dvec4 vPos;

out vec4 color;


void main()
{
	gl_Position = vec4(vPos);
	color = vec4(vColor);
}
