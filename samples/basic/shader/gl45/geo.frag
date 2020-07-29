#version 430 core

precision mediump int;
precision mediump float;
precision mediump sampler1D;
precision mediump sampler2D;
precision mediump sampler3D;
precision mediump samplerCube;
precision mediump sampler2DArray;
precision mediump samplerBuffer;


out vec4 FragColor;
in vec3 fColor;

void main()
{
	FragColor = vec4(fColor, 1.0);
}

