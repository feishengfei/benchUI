#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout(location = 0) in vec2 pos;
layout(location = 1) in vec4 col;

out vec4 oColor;

void main()
{
	gl_Position =  vec4(pos.x+0.2, pos.y+0.2, 0.0, 1.0);
	oColor = col;
}

