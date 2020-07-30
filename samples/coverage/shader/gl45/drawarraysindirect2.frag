#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


out vec4 fColor;

in vec4 oColor;

void main()
{
	fColor = vec4(0, 0, oColor.x, 1.0);
}
