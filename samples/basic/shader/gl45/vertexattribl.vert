#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


layout(location = 0) in dvec4 vColor;
layout(location = 1) in vec4 vPos;

out vec4 color;


void main()
{
	gl_Position = vPos;
	color = vec4(vColor);
}
