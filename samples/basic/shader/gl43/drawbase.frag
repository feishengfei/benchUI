#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


in vec4 verColor;
out vec4 FragColor;
layout(location = 0) uniform vec2 t;
void main()
{
	FragColor = vec4(verColor.r, t, 1.0);
}
