#version 430 core

precision highp float;
precision highp int;

layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 Texcoord;

out vec2 OutTexcoord;

void main()
{
	OutTexcoord = Texcoord;
	gl_Position = vec4(Position, 0.0, 1.0);
}
