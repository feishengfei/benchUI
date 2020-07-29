#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;



layout(location = 0) in vec2 Position;
layout(location = 1) in vec2 Texcoord;

out vec2 OutTexcoord;

void main()
{
	OutTexcoord = Texcoord;
	gl_Position = vec4(Position, 0.0, 1.0);
}
